
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
  osg::ref_ptr<osg::Group> Body::createOsgGeometry()
  { 
    // For now all Bodies are simple boxes centered on the robot's position
    // Position is specified relative to the geometric center of this Box
    //m_osgGeometry = new osg::Box( 
    //  osg::Vec3( m_dimensions.x() / 2.0, m_dimensions.y() / 2.0, m_dimensions.z() / 2.0 ),
    //  m_dimensions.x(), m_dimensions.y(), m_dimensions.z());
    
    m_osgGeometry = new osg::Box( 
      osg::Vec3( 0.0, 0.0, 0.0),
      m_dimensions.x(), m_dimensions.y(), m_dimensions.z());
    
    m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );
    m_osgTransform = new osg::PositionAttitudeTransform();
    
    m_osgTransform->setReferenceFrame( osg::Transform::ReferenceFrame::RELATIVE_RF );
    m_osgTransform->setPosition( osg::Vec3d( 0.0, 0.0, -1.0 ) );
    
    // Pointing directly into screen
    osg::Quat attitude;
    // TODO: For some reason the body ends up pointed along the y axis instead of z
    // The box itself may be confused as to l/w/d, or this stuff might be wrong
    // Shouldn't matter until we're interacting the something else in the environment
    
    //attitude.makeRotate( osg::DegreesToRadians(-90.0), osg::Vec3( 1.0, 0.0, 0.0 ) );
    
    m_osgTransform->setAttitude( attitude ) ;
    
    m_osgGeode = new osg::Geode();
    m_osgGeode->addDrawable( m_osgDrawable );
    m_osgTransform->addChild( m_osgGeode );
    
    // Add each of the appendages a child nodes
    for( std::shared_ptr<Joint>& joint : m_appendages )
    {
      osg::ref_ptr<osg::Group> appendageGroup{ joint->createOsgGeometry() };
      // Set position of joint
      // Set rotation of joint
      // Add to m_osgTransform
      m_osgTransform->addChild( appendageGroup );
    }
    return m_osgTransform;
  }
  
  osg::ref_ptr<osg::Group> Body::osgGeometry() const
  {
    return m_osgTransform;
  }
  
  void Body::updateOsgGeometry()
  {
    // TODO
    for( std::shared_ptr<Joint>& joint : m_appendages )
    {
      joint->updateOsgGeometry();
    }
  }
#endif
};

