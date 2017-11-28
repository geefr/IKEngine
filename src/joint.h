#ifndef JOINT_H
#define JOINT_H

#include "config.h"

#include "libikengine.h"
#include "servos/servo.h"

#include <memory>

#ifdef IKENGINE_OSG
# include <osg/Transform>
# include <osg/PositionAttitudeTransform>
# include <osg/Geometry>
# include <osg/ShapeDrawable>
#endif

namespace IKEngine
{
  class Limb;
  
  /**
   * A joint, rotateable in a single axis. i.e. A servo
   */
  class Joint
  {
    public:
      /**
       * Constructor
       * 
       * @param rotationAxis The axis of rotation. If looking along the limb the y-axis would result in the next limb pivoting on the joint.
       *                     The x-axis would result in the next limb moving up/down.
       * @param servo The servo for this joint. Ownership is transferred to the Joint
       */
      Joint( Servo* servo, const vec3& rotationAxis = { 1.0, 0.0, 0.0 } );
      ~Joint();

      std::shared_ptr<Limb> next() const;
      void next( std::shared_ptr<Limb> l );
      
      // Access the servo
      Servo& servo();

      // Position of the joint
      vec3& position();
      void position( const vec3& pos );
      
      // Rotation of the joint, also specifies the zero-point for the next limb
      // A limb with the default vector of (0,0,1) would point directly away from the joint
      vec3& rotation();
      void rotation( const vec3& rotation );
      
      // Axis of rotation for the servo
      vec3& servoAxis();
      void servoAxis( const vec3& rotAxis );
    
#ifdef IKENGINE_OSG
      // All geometry/nodes are created in this method, a fresh set is created every time
      osg::ref_ptr<osg::Group> createOsgGeometry();
      // Getter for the osg node
      osg::ref_ptr<osg::Group> osgGeometry() const;
      // Call to update the gometry for the robot's parameters
      void updateOsgGeometry();

    private:
      osg::ref_ptr<osg::PositionAttitudeTransform> m_osgTransform;
      osg::ref_ptr<osg::ShapeDrawable> m_osgDrawable;
      osg::ref_ptr<osg::Sphere> m_osgGeometry;
      osg::ref_ptr<osg::Geode> m_osgGeode;
#endif
    private:
      float m_degreeOffset;
      std::unique_ptr<Servo> m_servo;
      // Position (in parent's coordinate space)
      vec3 m_position;
      vec3 m_rotation;
      // Axis of rotation
      vec3 m_servoAxis;

      // The Limb attached to this joint
      // Normally pointing straight along m_direction
      std::shared_ptr<Limb> m_next;
  };
  
  inline Servo& Joint::servo() { return *m_servo; }

  inline vec3& Joint::position() { return m_position; }
  inline void Joint::position( const vec3& pos ) { m_position = pos; }
  
  inline vec3& Joint::rotation() { return m_rotation; }
  inline void Joint::rotation( const vec3& rot ) { m_rotation = rot; }
  
  inline vec3& Joint::servoAxis() { return m_servoAxis; }
  inline void Joint::servoAxis( const vec3& rotAxis ) { m_servoAxis = rotAxis; }
};

#endif
