
#ifndef DELTA_OBJECT_VIEWER_TYPEDEFS_H
#define DELTA_OBJECT_VIEWER_TYPEDEFS_H

////////////////////////////////////////////////////////////////////////////////
// INCLUDE DIRECTIVES
////////////////////////////////////////////////////////////////////////////////
#include <osg/Node>
#include <dtCore/shaderprogram.h>



////////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
////////////////////////////////////////////////////////////////////////////////
typedef dtCore::RefPtr<osg::Node> OsgNodePtr;
typedef std::vector<OsgNodePtr> OsgNodeArray;
typedef dtCore::RefPtr<dtCore::ShaderProgram> ShaderProgramPtr;

#endif