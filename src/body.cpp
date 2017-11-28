
#include "body.h"

#include <osg/Geometry>
#include <osg/ShapeDrawable>

namespace IKEngine
{
	Body::Body( const vec3& dimensions )
	: m_dimensions{ dimensions }
  , m_position{ 0.0, 0.0, 0.0 }
  , m_rotation{ 0.0, 0.0, 0.0 }
	{
	}
	
	Body::~Body()
	{}

  size_t Body::numAppendages() const
  {
    return m_appendages.size();
  }

  void Body::addAppendage( std::shared_ptr<Joint> appendage,
    const vec3& position, const vec3& rotation, const vec3& servoAxis )
  {
    m_appendages.emplace_back( appendage );
    // Update position and zero vector for root joint
    // All objects are positioned relative to their parent
    appendage->position() = position;
    appendage->rotation() = rotation;
    appendage->servoAxis() = servoAxis;
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
    m_osgGeometry = new osg::Box( 
      osg::Vec3( 0.0, 0.0, 0.0),
      m_dimensions.x(), m_dimensions.y(), m_dimensions.z());
    
    m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );
    m_osgDrawable->setColor( osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );
    
    m_osgTransform = new osg::PositionAttitudeTransform();
    m_osgTransform->setReferenceFrame( osg::Transform::ReferenceFrame::RELATIVE_RF );
    m_osgTransform->setPosition( osg::Vec3d( m_position.x(), m_position.y(), m_position.z() ) );
    
    // +90 degrees in X for IKEngine -> osg
    osg::Quat attitude( m_rotation.x() + osg::PI_2, osg::X_AXIS,
                        m_rotation.y(), osg::Y_AXIS,
                        m_rotation.z(), osg::Z_AXIS );
    
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
    if( !m_osgTransform ) return;
    
    m_osgTransform->setPosition( osg::Vec3d( m_position.x(), m_position.y(), m_position.z() ) );
    // +90 degrees in X for IKEngine -> osg
    osg::Quat attitude( m_rotation.x() + osg::PI_2, osg::X_AXIS,
                        m_rotation.y(), osg::Y_AXIS,
                        m_rotation.z(), osg::Z_AXIS );
    m_osgTransform->setAttitude( attitude ) ;
    
    for( std::shared_ptr<Joint>& joint : m_appendages )
    {
      joint->updateOsgGeometry();
    }
  }
#endif
};

