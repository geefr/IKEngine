
#include "body.h"

#include <osg/Geometry>
#include <osg/ShapeDrawable>

namespace IKEngine
{
	Body::Body( const vec3& dimensions )
	: m_dimensions{ dimensions }
	{
	}
	
	Body::~Body()
	{}

  size_t Body::numAppendages() const
  {
    return m_appendages.size();
  }

  void Body::addAppendage( std::shared_ptr<Joint> appendage,
    const vec3& position, const vec3& direction, const vec3& up )
  {
    m_appendages.emplace_back( appendage );
    // Update position and zero vector for root joint
    // All objects are positioned relative to their parent
    appendage->position() = position;
    appendage->direction() = direction;
    appendage->up() = up;
#ifdef IKENGINE_OSG

#endif
  }

  std::shared_ptr<Joint> Body::getAppendage( size_t i )
  {
    return m_appendages[i];
  }

  void Body::removeAppendage( size_t i )
  {
    m_appendages.erase( m_appendages.begin() + i );
  }

#ifdef IKENGINE_OSG
	osg::ref_ptr<osg::Drawable> Body::osgGeometry() const
	{
		if( m_osgDrawable )
		{
			return m_osgDrawable;
		}

		m_osgGeometry = new osg::Box( 
		  osg::Vec3(0.0, 0.0, 0.0),
		  m_dimensions.x(), m_dimensions.y(), m_dimensions.z());
		m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );

		// Add each of the appendages a child nodes
		for( std::shared_ptr<Joint>& joint : m_appendages )
		{
			osg::ref_ptr<osg::Geometry> geom{ joint->osgGeometry() };
            
		}

		return m_osgDrawable;
	}
#endif
};

