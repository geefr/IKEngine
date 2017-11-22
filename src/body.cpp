
#include "body.h"

#include <osg/Geometry>
#include <osg/ShapeDrawable>

namespace IKEngine
{
	Body::Body()
	{
#ifdef IKENGINE_OSG
		m_osgGeometry = new osg::Box( 
		  osg::Vec3(0.0, 0.0, 0.0),
		  6, 3, 1);
		m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );
#endif
	}
	
	Body::~Body()
	{}

#ifdef IKENGINE_OSG
	osg::ref_ptr<osg::Drawable> Body::osgGeometry() const
	{
		return m_osgDrawable;
	}
#endif
};

