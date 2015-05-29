/* -*-c++-*-
 * Delta3D Open Source Game and Simulation Engine
 * Copyright (C) 2015, Caper Holdings, LLC
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
 */

#include <dtVoxel/voxelactor.h>
#include <dtVoxel/voxelgriddebugdrawable.h>

#include <dtABC/application.h>

#include <dtCore/transformable.h>
#include <dtCore/propertymacros.h>
#include <dtCore/camera.h>
#include <dtCore/project.h>
#include <dtCore/transform.h>

#include <dtGame/basemessages.h>
#include <dtGame/gamemanager.h>

#include <openvdb/openvdb.h>
#include <dtVoxel/aabbintersector.h>

namespace dtVoxel
{

   VoxelActor::VoxelActor()
   {
   }

   VoxelActor::~VoxelActor()
   {
   }

   /////////////////////////////////////////////////////
   DT_IMPLEMENT_ACCESSOR_WITH_STATEMENT(VoxelActor, dtCore::ResourceDescriptor, Database, LoadGrid(value););

   /////////////////////////////////////////////////////
   void VoxelActor::LoadGrid(const dtCore::ResourceDescriptor& rd)
   {
      if (rd != GetDatabase() && !rd.IsEmpty())
      {
         try
         {
            openvdb::io::File file(dtCore::Project::GetInstance().GetResourcePath(rd));
            file.open();
            mGrids = file.getGrids();
            file.close();
         }
         catch (const openvdb::IoError& ioe)
         {
            throw dtUtil::FileUtilIOException(ioe.what(), __FILE__, __LINE__);
         }
      }
      else if (rd.IsEmpty())
      {
         mGrids = NULL;
      }
   }

   /////////////////////////////////////////////////////
   void VoxelActor::BuildPropertyMap()
   {
      BaseClass::BuildPropertyMap();

      typedef dtCore::PropertyRegHelper<VoxelActor> RegHelper;
      static dtUtil::RefString GROUP("VoxelActor");
      RegHelper regHelper(*this, this, GROUP);
      
      DT_REGISTER_PROPERTY_WITH_NAME_AND_LABEL(ViewDistance, "View Distance", "View Distance", "The distance to at which voxels will be generated into groups of volumes and rendered.", RegHelper, regHelper);
      DT_REGISTER_PROPERTY_WITH_NAME_AND_LABEL(GridDimensions, "Grid Dimensions", "Grid Dimensions", "The size of the grid to allocate into blocks.", RegHelper, regHelper);
      DT_REGISTER_PROPERTY_WITH_NAME_AND_LABEL(BlockDimensions, "Block Dimensions", "Block Dimensions", "The size of the blocks within the grid.", RegHelper, regHelper);
      DT_REGISTER_PROPERTY_WITH_NAME_AND_LABEL(CellDimensions, "Cell Dimensions", "Cell Dimensions", "The size of the cells within the blocks", RegHelper, regHelper);
      DT_REGISTER_PROPERTY_WITH_NAME_AND_LABEL(TextureResolution, "Texture Resolution", "Texture Resolution", "The dimensions of the 3d texture which holds individual voxels within a single cell.", RegHelper, regHelper);

      DT_REGISTER_RESOURCE_PROPERTY(dtCore::DataType::VOLUME, Database, "Database", "Voxel database file", RegHelper, regHelper);
   }

   /////////////////////////////////////////////////////
   openvdb::GridPtrVecPtr VoxelActor::GetGrids()
   {
      return mGrids;
   }

   /////////////////////////////////////////////////////
   openvdb::GridBase::Ptr VoxelActor::GetGrid(int i)
   {
      if (mGrids) return (*mGrids)[i];
      return NULL;
   }

   /////////////////////////////////////////////////////
   size_t VoxelActor::GetNumGrids() const
   {
      size_t result = 0;
      if (mGrids) result = mGrids->size();
      return result;
   }

   /////////////////////////////////////////////////////
   openvdb::GridBase::Ptr VoxelActor::CollideWithAABB(osg::BoundingBox& bb, int gridIdx)
   {
      openvdb::GridBase::Ptr result(NULL);
      openvdb::BBoxd bbox(openvdb::Vec3d(bb.xMin(), bb.yMin(), bb.zMin()), openvdb::Vec3d(bb.xMax(), bb.yMax(), bb.zMax()));
      if (openvdb::BoolGrid::Ptr gridB = boost::dynamic_pointer_cast<openvdb::BoolGrid>(GetGrid(gridIdx)))
      {
         AABBIntersector<openvdb::BoolGrid> aabb(gridB);
         aabb.SetWorldBB(bbox);
         aabb.Intersect();
         result = aabb.GetHits();
       }
      else if (openvdb::FloatGrid::Ptr gridF = boost::dynamic_pointer_cast<openvdb::FloatGrid>(GetGrid(gridIdx)))
      {
         AABBIntersector<openvdb::FloatGrid> aabb(gridF);
         aabb.SetWorldBB(bbox);
         aabb.Intersect();
         result = aabb.GetHits();
      }
      return result;
   }
   
   void VoxelActor::OnTickLocal(const dtGame::TickMessage& tickMessage)
   {
      if (mGrid.valid())
      {
         dtGame::GameManager* gm = GetGameManager();

         if (gm != nullptr)
         {
            dtCore::Camera* cam = gm->GetApplication().GetCamera();

            osg::Vec3 pos;
            dtCore::Transform xform;
            cam->GetTransform(xform);
            xform.GetTranslation(pos);

            mGrid->UpdateGrid(pos);

            //std::cout << "Updating voxel grid with position (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << std::endl;
         }
      }
   }


   /////////////////////////////////////////////////////
   void VoxelActor::CreateDrawable()
   {
      //commented out, this is a simple debug rendering
      //dtCore::RefPtr<VoxelGridDebugDrawable> dd = new VoxelGridDebugDrawable();
      //dd->CreateDebugDrawable(*mGrid);
      //SetDrawable(*dd);

      mGrid = new VoxelGrid();
      SetDrawable(*mGrid);

   }


   void VoxelActor::OnEnteredWorld()
   {
      RegisterForMessages(dtGame::MessageType::TICK_LOCAL, dtGame::GameActorProxy::TICK_LOCAL_INVOKABLE);

      openvdb::BoolGrid::Ptr gridB = boost::dynamic_pointer_cast<openvdb::BoolGrid>(GetGrid(0));

      /*osg::Vec3 offset(-2500.0, -2500.0, -9.0);
      osg::Vec3 dim(5000, 5000, 18);
      osg::Vec3 blockDim(50, 50, 6);
      osg::Vec3 cellDim(12.5, 12.5, 2);
      osg::Vec3i texRes(24, 24, 4);

      mGrid->SetViewDistance(1000.0f);*/
      osg::Vec3i res(int(mTextureResolution.x()), int(mTextureResolution.y()), int(mTextureResolution.z()));
      osg::Vec3 offset = GetTranslation();

      mGrid->Init(offset, mGridDimensions, mBlockDimensions, mCellDimensions, res);
      
      osg::Vec3 pos(0.0f, 0.0f, 0.0f);
      mGrid->CreateGridFromActor(pos, *this);

   }


} /* namespace dtVoxel */