
#include "limb.h"

#include "joint.h"

namespace IKEngine
{
  Limb::Limb( float length, const vec3& limbVector )
  : m_length{ length }
  , m_limbVector{ limbVector }
  {
    m_limbVector.normalize();
  }

  Limb::~Limb()
  {
    
  }

#ifdef IKENGINE_OSG
  osg::ref_ptr<osg::Group> Limb::createOsgGeometry()
  {
    m_osgTransform = new osg::Transform();

    m_osgGeometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> vertices{ new osg::Vec3Array() };
    // Position of the parent joint, relative to the parent joint's transform
    vertices->push_back( osg::Vec3(0.0, 0.0, 0.0) );
    // Other end of this limb
    vertices->push_back( osg::Vec3(m_limbVector.x(), m_limbVector.y(), m_limbVector.z()) );

    osg::ref_ptr<osg::Vec4Array> colour{ new osg::Vec4Array };
    colour->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
    colour->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));

    vertices->setBinding( osg::Array::BIND_PER_VERTEX );

    m_osgGeometry->setVertexArray(vertices.get());
    m_osgGeometry->setColorArray(colour.get());
    m_osgGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));
    
    m_osgGeode = new osg::Geode();
    m_osgTransform->addChild( m_osgGeode );
    m_osgGeode->addDrawable( m_osgGeometry );

    if( m_frontJoint )
    {
      m_osgTransform->addChild( m_frontJoint->createOsgGeometry() );
    }

    return m_osgTransform;
  }
 
  osg::ref_ptr<osg::Group> Limb::osgGeometry() const
  {
    return m_osgTransform;
  }
  
  void Limb::updateOsgGeometry()
  {
    if( m_frontJoint )
    {
      m_frontJoint->updateOsgGeometry();
    }
  }
#endif
};
