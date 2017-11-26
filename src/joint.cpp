
#include "joint.h"
#include "limb.h"

#ifdef IKENGINE_OSG
# include <osg/ShapeDrawable>
#endif

namespace IKEngine
{
  Joint::Joint( Servo* servo, float degreeOffset, const vec3& rotationAxis )
  : m_degreeOffset( degreeOffset )
  , m_servo{ servo }
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
    // Position relative to parent
    //m_osgTransform->setReferenceFrame( osg::Transform::ReferenceFrame::RELATIVE_RF );
    
    m_osgTransform->setPosition( osg::Vec3d( m_position.x(), m_position.y(), m_position.z() ) );
    // TODO
    //m_osgTransform->setAttitude( osg::Quat( 0.0, 1.0, 0.0, 1.0 ) ) ;
    
    m_osgGeometry = new osg::Sphere();
    m_osgGeometry->setRadius(0.1);
    
    m_osgDrawable = new osg::ShapeDrawable( m_osgGeometry );
    
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
    // TODO
    m_osgTransform->setAttitude( osg::Quat( 0.0, 1.0, 0.0, 1.0 ) ) ;
    
    if( !m_next )
    {
      return;
    }
    m_next->updateOsgGeometry();
  }
#endif  
};
