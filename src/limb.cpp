
#include "limb.h"

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

# ifdef IKENGINE_OSG
  osg::ref_ptr<osg::Geometry> Limb::osgGeometry() const
  {
    if( m_osgGeometry )
    {
      return m_osgGeometry;
    }

    m_osgGeometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> vertices{ new osg::Vec3Array() };
    vertices->push_back( osg::Vec3(0.0, 0.0, 0.0) );
    vertices->push_back( osg::Vec3(limbVector.x(), limbVector.y(), limbVector.z()) );

    osg::ref_ptr<osg::Vec4Array> colour{ new osg::Vec4Array };
    colour->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));

    vertices->setBinding( osg::Array::BIND_PER_VERTEX );

    m_osgGeometry->setVertexArray(vertices.get());
    m_osgGeometry->setColorArray(colour.get());
    m_osgGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));

    return m_osgGeometry;
  }
# endif
#endif
};
