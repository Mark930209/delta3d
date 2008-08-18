/* -*-c++-*-
 * Delta3D Open Source Game and Simulation Engine
 * Copyright (C) 2007, Alion Science and Technology
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Bradley Anderegg 03/28/2007
 */
#include <dtAnim/animnodebuilder.h>
#include <dtAnim/cal3dmodelwrapper.h>
#include <dtAnim/submesh.h>
#include <dtAnim/hardwaresubmesh.h>
#include <dtAnim/cal3ddatabase.h>
#include <dtAnim/cal3dmodeldata.h>

#include <dtCore/globals.h>
#include <dtCore/shaderprogram.h>
#include <dtCore/shadermanager.h>
#include <dtCore/shadergroup.h>
#include <dtUtil/log.h>
#include <dtUtil/macros.h>

#include <osg/Geode>
#include <osg/State>
#include <osg/BoundingSphere>
#include <osg/BoundingBox>
#include <osg/Texture2D>
#include <osg/GLExtensions>
#include <osg/ShapeDrawable>

#include <cal3d/hardwaremodel.h>

//For the bounding box class, who knew.
#include <cal3d/vector.h>

namespace dtAnim
{

   ///Used to delay the building of the animated characters geometry until
   ///it is first rendered, at which point a valid OpenGL context should be valid
   class CreateGeometryDrawCallback : public osg::Drawable::DrawCallback
   {
   public:
      CreateGeometryDrawCallback(osg::Geode& geode, AnimNodeBuilder::CreateFunc& func,
                                 Cal3DModelWrapper* wrapper):
         mGeode(&geode)
         ,mCreateFunc(func)
         ,mWrapper(wrapper)
         {
         };

         ~CreateGeometryDrawCallback() {};

         virtual void drawImplementation(osg::RenderInfo&, const osg::Drawable*) const
         {
             mCreateFunc(*mGeode, mWrapper);
         }

   private:
      osg::ref_ptr<osg::Geode> mGeode;
      AnimNodeBuilder::CreateFunc mCreateFunc;
      Cal3DModelWrapper *mWrapper;
   };


AnimNodeBuilder::AnimNodeBuilder()
{
   if (SupportsHardware())
   {
      SetCreate(CreateFunc(this, &AnimNodeBuilder::CreateHardware));
   }
   else if (SupportsSoftware())
   {
      SetCreate(CreateFunc(this, &AnimNodeBuilder::CreateSoftware));
   }
   else
   {
      SetCreate(CreateFunc(this, &AnimNodeBuilder::CreateNULL));     
   }
}

AnimNodeBuilder::AnimNodeBuilder(const CreateFunc& pCreate)
: mCreateFunc(pCreate)
{  
}


AnimNodeBuilder::~AnimNodeBuilder()
{
   
}

AnimNodeBuilder::CreateFunc& AnimNodeBuilder::GetCreate()
{
   return mCreateFunc;
}

void AnimNodeBuilder::SetCreate(const CreateFunc& pCreate)
{
   mCreateFunc = pCreate;
}


dtCore::RefPtr<osg::Node> AnimNodeBuilder::CreateNode(Cal3DModelWrapper* pWrapper)
{
   ///build a temporary rendered shape and assign a draw callback to it which
   ///will postpone the creation of the real geometry until a valid openGL 
   ///context is available.
   osg::Geode* geode = new osg::Geode();
   osg::Cylinder *shape = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 1.f, 2.f);
   osg::ShapeDrawable *drawable = new osg::ShapeDrawable(shape);

   CreateGeometryDrawCallback *callback = new CreateGeometryDrawCallback(*geode, mCreateFunc, pWrapper);

   drawable->setDrawCallback(callback);
   geode->addDrawable(drawable);
   return geode;
}


bool AnimNodeBuilder::CreateSoftware(osg::Geode& geode, Cal3DModelWrapper* pWrapper)
{
   if(pWrapper == NULL)
   {
      LOG_ERROR("Invalid parameter to CreateGeode.");
      return false;
   }

   //remove existing callback and default geometry
   osg::Drawable *defaultDrawable = geode.getDrawable(0);
   if (defaultDrawable != NULL)
   {
      defaultDrawable->setDrawCallback(NULL);
      geode.removeDrawable(defaultDrawable);
   }

   geode.setComputeBoundingSphereCallback(new Cal3DBoundingSphereCalculator(*pWrapper));

   if(pWrapper->BeginRenderingQuery()) 
   {
      int meshCount = pWrapper->GetMeshCount();

      for(int meshId = 0; meshId < meshCount; meshId++) 
      {
         int submeshCount = pWrapper->GetSubmeshCount(meshId);

         for(int submeshId = 0; submeshId < submeshCount; submeshId++) 
         {
            dtAnim::SubmeshDrawable *submesh = new dtAnim::SubmeshDrawable(pWrapper, meshId, submeshId);
            geode.addDrawable(submesh);
         }
      }

      pWrapper->EndRenderingQuery();
   }

   pWrapper->Update(0);

   return true;
}

bool AnimNodeBuilder::CreateHardware(osg::Geode& geode, Cal3DModelWrapper* pWrapper)
{
   if(pWrapper == NULL)
   {
      LOG_ERROR("Invalid parameter to CreateGeode.");
      return false;
   }

   Cal3DModelData* modelData = Cal3DDatabase::GetInstance().GetModelData(*pWrapper);
   
   if (modelData == NULL)
   {
      LOG_ERROR("Model does not have model data.  Unable to create hardware submesh.");
      return false;
   }

   //remove existing callback and default geometry
   osg::Drawable *defaultDrawable = geode.getDrawable(0);
   if (defaultDrawable != NULL)
   {
      defaultDrawable->setDrawCallback(NULL);
      geode.removeDrawable(defaultDrawable);
   }  

   static const std::string BONE_TRANSFORM_UNIFORM("boneTransforms");

   pWrapper->SetLODLevel(1);
   pWrapper->Update(0);

   if(pWrapper->BeginRenderingQuery() == false) 
   {
      LOG_ERROR("Can't begin the rendering query.");
      return false;
   }

   int numVerts = 0;
   int numIndices = 0;

   CalcNumVertsAndIndices(pWrapper, numVerts, numIndices);

   const size_t stride = 18;
   const size_t strideBytes = stride * sizeof(float);

   Array<CalIndex> indexArray(numIndices);

   CalHardwareModel* hardwareModel = pWrapper->GetOrCreateCalHardwareModel();

   osg::Drawable::Extensions* glExt = osg::Drawable::getExtensions(0, true);
   GLuint vbo[2];
   if (modelData->GetVertexVBO() == 0)
   {
      glExt->glGenBuffers(1, &vbo[0]);
      glExt->glBindBuffer(GL_ARRAY_BUFFER_ARB, vbo[0]);
      glExt->glBufferData(GL_ARRAY_BUFFER_ARB, strideBytes * numVerts, NULL, GL_STATIC_DRAW_ARB);
      modelData->SetVertexVBO(vbo[0]);
   }
   else
   {
      vbo[0] = modelData->GetVertexVBO();
      glExt->glBindBuffer(GL_ARRAY_BUFFER_ARB, vbo[0]);
   }

   bool newIndexBuffer = false;
   if (modelData->GetIndexVBO() == 0)
   {
      glExt->glGenBuffers(1, &vbo[1]);
      modelData->SetIndexVBO(vbo[1]);
      newIndexBuffer = true;
   }
   else
   {
      vbo[1] = modelData->GetIndexVBO();
   }

   hardwareModel->setIndexBuffer(indexArray.mArray);

   float* vboVertexAttr = static_cast<float*>(glExt->glMapBuffer(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB));

   hardwareModel->setVertexBuffer(reinterpret_cast<char*>(vboVertexAttr), strideBytes);
   hardwareModel->setNormalBuffer(reinterpret_cast<char*>(vboVertexAttr + 3), strideBytes);

   hardwareModel->setTextureCoordNum(2);
   hardwareModel->setTextureCoordBuffer(0, reinterpret_cast<char*>(vboVertexAttr + 6), strideBytes);
   hardwareModel->setTextureCoordBuffer(1, reinterpret_cast<char*>(vboVertexAttr + 8), strideBytes);

   hardwareModel->setWeightBuffer(reinterpret_cast<char*>(vboVertexAttr + 10), strideBytes);
   hardwareModel->setMatrixIndexBuffer(reinterpret_cast<char*>(vboVertexAttr + 14), strideBytes);
      
   if(hardwareModel->load(0, 0, modelData->GetShaderMaxBones()))
   {

      InvertTextureCoordinates(hardwareModel, stride, vboVertexAttr, modelData, indexArray);

      const int numIndices = 3 * hardwareModel->getTotalFaceCount();

      glExt->glUnmapBuffer(GL_ARRAY_BUFFER_ARB);
      if (newIndexBuffer)
      {
         glExt->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, vbo[1]);
         glExt->glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, numIndices * sizeof(CalIndex), (const void*) indexArray.mArray, GL_STATIC_DRAW_ARB);
      }

      dtCore::ShaderProgram* shadProg = LoadShaders(*modelData, geode);

      /* Begin figure out if this open gl implementation uses [0] on array uniforms 
      * This seems to be an ATI/NVIDIA thing.  
      * This requires me to force the shader to compile.
      */
      osg::Program* prog = shadProg->GetShaderProgram();
      dtCore::RefPtr<osg::State> tmpState = new osg::State;
      tmpState->setContextID(0);
      prog->compileGLObjects(*tmpState);
      const osg::Program::ActiveVarInfoMap& uniformMap = prog->getActiveUniforms(0);

      std::string boneTransformUniform = BONE_TRANSFORM_UNIFORM;
      if (uniformMap.find(boneTransformUniform) == uniformMap.end())
      {
         if (uniformMap.find(boneTransformUniform + "[0]") == uniformMap.end())
         {
            LOG_ERROR("Can't find uniform named \"" + boneTransformUniform 
               + "\" which is required for skinning.");
         }
         else
         {
            boneTransformUniform.append("[0]");
         }
      }
      // End check.

      for(int meshCount = 0; meshCount < hardwareModel->getHardwareMeshCount(); ++meshCount)
      {
         HardwareSubmeshDrawable* drawable = new HardwareSubmeshDrawable(pWrapper, hardwareModel, 
                                                 boneTransformUniform, modelData->GetShaderMaxBones(),
                                                 meshCount, vbo[0], vbo[1]);
         geode.addDrawable(drawable);
      }

      geode.setComputeBoundingSphereCallback(new Cal3DBoundingSphereCalculator(*pWrapper));
   }
   else
   {
      glExt->glUnmapBuffer(GL_ARRAY_BUFFER_ARB);
      LOG_ERROR("Unable to create a hardware mesh:" + CalError::getLastErrorDescription() );
   }

   glExt->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
   glExt->glBindBuffer(GL_ARRAY_BUFFER_ARB, 0);

   pWrapper->EndRenderingQuery();   

   return true;
}

bool AnimNodeBuilder::CreateNULL(osg::Geode& geode, Cal3DModelWrapper* pWrapper)
{
   UNREFERENCED_PARAMETER(pWrapper);

   //remove existing callback and default geometry
   osg::Drawable *defaultDrawable = geode.getDrawable(0);
   if (defaultDrawable != NULL)
   {
      defaultDrawable->setDrawCallback(NULL);
      geode.removeDrawable(defaultDrawable);
   }

   //NULL create function.  Used if hardware and software create functions fail.
   return true;
}


dtCore::ShaderProgram* AnimNodeBuilder::LoadShaders(Cal3DModelData& modelData, osg::Geode& geode) const
{
   static const std::string hardwareSkinningSPGroup = "HardwareSkinning";
   dtCore::ShaderManager& shaderManager = dtCore::ShaderManager::GetInstance();
   dtCore::ShaderProgram* shaderProgram = NULL;
   if (!modelData.GetShaderGroupName().empty())
   {
      dtCore::ShaderGroup* spGroup = shaderManager.FindShaderGroupPrototype(modelData.GetShaderGroupName());
      if (spGroup != NULL)
      {
         if (!modelData.GetShaderName().empty())
         {
            shaderProgram = spGroup->FindShader(modelData.GetShaderName());
            if (shaderProgram == NULL)
            {
               LOG_ERROR("Shader program \"" + modelData.GetShaderName() + "\" from group \"" 
                     + modelData.GetShaderGroupName() + "\" was not found, using the default from the group.");
               shaderProgram = spGroup->GetDefaultShader();
               
               if (shaderProgram == NULL)
               {
                  LOG_ERROR("Shader Group \""  + modelData.GetShaderGroupName() 
                        + "\" was not found, overriding to use the default group.");
               }
            }
         }
         else
         {
            shaderProgram = spGroup->GetDefaultShader();
            if (shaderProgram == NULL)
            {
               LOG_ERROR("Shader Group \""  + modelData.GetShaderGroupName() 
                     + "\" was not found, overriding to use the default group.");
            }
         }
      }
   }
   
   //If no shader group is setup, create one.
   if (shaderProgram == NULL)
   {
      dtCore::ShaderGroup* defSPGroup = shaderManager.FindShaderGroupPrototype(hardwareSkinningSPGroup);
      if (defSPGroup == NULL)
      {
         defSPGroup = new dtCore::ShaderGroup(hardwareSkinningSPGroup);
         shaderProgram = new dtCore::ShaderProgram("Default");
         shaderProgram->AddVertexShader("shaders/HardwareCharacter.vert");
         defSPGroup->AddShader(*shaderProgram, true);
         shaderManager.AddShaderGroupPrototype(*defSPGroup);
      }
      else
      {
         shaderProgram = defSPGroup->GetDefaultShader();
      }
      modelData.SetShaderGroupName(hardwareSkinningSPGroup);
   }
   return shaderManager.AssignShaderFromPrototype(*shaderProgram, geode);
}

AnimNodeBuilder::Cal3DBoundingSphereCalculator::Cal3DBoundingSphereCalculator(Cal3DModelWrapper& wrapper)
   : mWrapper(&wrapper)
{
}

osg::BoundingSphere AnimNodeBuilder::Cal3DBoundingSphereCalculator::computeBound(const osg::Node&) const
{ 
   CalBoundingBox& calBBox = mWrapper->GetCalModel()->getBoundingBox(false);
   osg::BoundingBox bBox(-calBBox.plane[0].d, -calBBox.plane[2].d, -calBBox.plane[4].d,
         calBBox.plane[1].d, calBBox.plane[3].d, calBBox.plane[5].d);

   osg::BoundingSphere bSphere(bBox);
   return bSphere;
}

void AnimNodeBuilder::CalcNumVertsAndIndices( Cal3DModelWrapper* pWrapper,
                                             int &numVerts, int &numIndices)
{
   CalCoreModel* model = pWrapper->GetCalModel()->getCoreModel();


   const int meshCount = model->getCoreMeshCount();

   for(int meshId = 0; meshId < meshCount; meshId++) 
   {
      CalCoreMesh* calMesh = model->getCoreMesh(meshId);
      int submeshCount = calMesh->getCoreSubmeshCount();

      for(int submeshId = 0; submeshId < submeshCount; submeshId++) 
      {
         CalCoreSubmesh* subMesh = calMesh->getCoreSubmesh(submeshId);
         numVerts += subMesh->getVertexCount();
         numIndices += 3 * subMesh->getFaceCount();
      }
   }
}

void AnimNodeBuilder::InvertTextureCoordinates( CalHardwareModel* hardwareModel, const size_t stride,
                                                float* vboVertexAttr, Cal3DModelData* modelData,
                                                Array<CalIndex> &indexArray )
{
   const int numVerts = hardwareModel->getTotalVertexCount();
   //invert texture coordinates.
   for(unsigned i = 0; i < numVerts * stride; i += stride)
   {
      for (unsigned j = 15; j < 18; ++j)
      {
         if (vboVertexAttr[i + j] > modelData->GetShaderMaxBones())
         {
            vboVertexAttr[i + j] = 0;
         }
      }

      vboVertexAttr[i + 7] = 1.0f - vboVertexAttr[i + 7]; //the odd texture coordinates in cal3d are flipped, not sure why
      vboVertexAttr[i + 9] = 1.0f - vboVertexAttr[i + 9]; //the odd texture coordinates in cal3d are flipped, not sure why
   }

   for(int meshCount = 0; meshCount < hardwareModel->getHardwareMeshCount(); ++meshCount)
   {
      hardwareModel->selectHardwareMesh(meshCount);

      for(int face = 0; face < hardwareModel->getFaceCount(); ++face) 
      {
         for(int index = 0; index < 3; ++index)
         {
            indexArray[face * 3 + index + hardwareModel->getStartIndex()] += hardwareModel->getBaseVertexIndex();
         }
      }
   }
}

//////////////////////////////////////////////////////////////////////////
bool AnimNodeBuilder::SupportsHardware() const
{
   //check if hardware supports our requirements
   return SupportsVertexBuffers();
}

//////////////////////////////////////////////////////////////////////////
bool AnimNodeBuilder::SupportsSoftware() const
{
   //check if hardware supports our requirements
   return SupportsVertexBuffers();
}

//////////////////////////////////////////////////////////////////////////
bool AnimNodeBuilder::SupportsVertexBuffers() const
{
   //see if we can support vertex buffer objects
   osg::Drawable::getExtensions(0, true);
   
   return (osg::isGLExtensionSupported(0, "GL_ARB_vertex_buffer_object"));
}


}//namespace dtAnim
