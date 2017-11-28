
#include "joint.h"
#include "limb.h"

#ifdef IKENGINE_OSG
# include <osg/ShapeDrawable>
#endif

namespace IKEngine
{
  Joint::Joint( Servo* servo, const vec3& rotationAxis )
  : m_servo{ servo }
  , m_position{ 0.0, 0.0, 0.0 }
  , m_rotation{ 0.0, 0.0, 0.0 }
  , m_servoAxis{ rotationAxis }
  {
    
  }
  
  Joint::~Joint()
  {
    
  }

  std::shared_ptr<Limb> Joint::next() const
  {
    return m_next;
  }

  void Joint::next( std::shared_ptr<Limb> l )
  {
    m_next = l;
  }
  
#ifdef IKENGINE_OSG
  // All geometry/nodes are created in this method, a fresh set is created every time
  osg::ref_ptr<osg::Group> Joint::createOsgGeometry()
  {
    m_osgTransform = new osg::PositionAttitudeTransform();
    m_osgTransform->setReferenceFrame( osg::Transform::ReferenceFrame::RELATIVE_RF );
    m_osgTransform->setPosition( osg::Vec3d( m_position.x(), m_position.y(), m_position.z() ) );
    
    // +90 degrees in X for IKEngine -> osg
    // Rotation of joint itself
    osg::Quat attitude( m_rotation.x() + osg::PI_2, osg::X_AXIS,
                        m_rotation.y(), osg::Y_AXIS,
                        m_rotation.z(), osg::Z_AXIS );
    // Rotation from the servo
    float servoRot{ osg::DegreesToRadians(m_servo->get()) };
    osg::Quat servoAttitude( (m_servoAxis.x() * servoRot) + osg::PI_2, osg::X_AXIS,
                             (m_servoAxis.y() * servoRot), osg::Y_AXIS,
                             (m_servoAxis.z() * servoRot), osg::Z_AXIS );
    
    m_osgTransform->setAttitude( attitude * servoAttitude ) ;
    
    m_osgGeometry = new osg::Sphere();
    m_osgGeometry->setRadius(0.02);
    
    m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );
    m_osgDrawable->setColor( osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );
    
    m_osgGeode = new osg::Geode();
    m_osgGeode->addDrawable( m_osgDrawable );
    m_osgTransform->addChild( m_osgGeode );
    
    if( m_next )
    {
      m_osgTransform->addChild( m_next->createOsgGeometry() );
    }
    return m_osgTransform;
  }
  
  // Getter for the osg node
  osg::ref_ptr<osg::Group> Joint::osgGeometry() const
  {
    return m_osgTransform;
  }
  
  // Call to update the gometry for the robot's parameters
  void Joint::updateOsgGeometry()
  {
    if( !m_osgTransform ) return;
    
    m_osgTransform->setPosition( osg::Vec3d( m_position.x(), m_position.y(), m_position.z() ) );
    // +90 degrees in X for IKEngine -> osg
    float servoRot{ osg::DegreesToRadians(m_servo->get()) };
    osg::Quat attitude( m_rotation.x() + osg::PI_2, osg::X_AXIS,
                        m_rotation.y(), osg::Y_AXIS,
                        m_rotation.z(), osg::Z_AXIS );
    osg::Quat servoAttitude( (m_servoAxis.x() * servoRot) + osg::PI_2, osg::X_AXIS,
                         (m_servoAxis.y() * servoRot), osg::Y_AXIS,
                         (m_servoAxis.z() * servoRot), osg::Z_AXIS );
    m_osgTransform->setAttitude( attitude * servoAttitude ) ;
    
    if( !m_next )
    {
      return;
    }
    m_next->updateOsgGeometry();
  }
#endif  
};
