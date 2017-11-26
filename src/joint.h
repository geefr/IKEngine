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
# include <osg/Drawable>
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
       * @param degreeOffset The starting offset in degrees of the rotation
       * @param rotationAxis The axis of rotation. If looking along the limb the y-axis would result in the next limb pivoting on the joint.
       *                     The x-axis would result in the next limb moving up/down.
       * @param servo The servo for this joint. Ownership is transferred to the Joint
       */
      Joint( Servo* servo, float degreeOffset = 0.0, const vec3& rotationAxis = { 1.0, 0.0, 0.0 } );
      ~Joint();

      std::shared_ptr<Limb> next() const;
      void next( std::shared_ptr<Limb> l );

      vec3& position();
      vec3& direction();
      vec3& up();
    
#ifdef IKENGINE_OSG
      // All geometry/nodes are created in this method, a fresh set is created every time
      osg::ref_ptr<osg::Group> createOsgGeometry();
      // Getter for the osg node
      osg::ref_ptr<osg::Group> osgGeometry() const;
      // Call to update the gometry for the robot's parameters
      void updateOsgGeometry();

    private:
      osg::ref_ptr<osg::PositionAttitudeTransform> m_osgTransform;
      osg::ref_ptr<osg::Drawable> m_osgDrawable;
      osg::ref_ptr<osg::Sphere> m_osgGeometry;
      osg::ref_ptr<osg::Geode> m_osgGeode;
#endif
    private:
      float m_degreeOffset;
      std::unique_ptr<Servo> m_servo;
      // Position (in parent's coordinate space)
      vec3 m_position;
      // Direction corresponding to zero degrees
      vec3 m_direction;
      // The up vector. All joints rotate around the x axis (Along this vector)
      vec3 m_up;

      // The Limb attached to this joint
      // Normally pointing straight along m_direction
      std::shared_ptr<Limb> m_next;
  };

  inline vec3& Joint::position() { return m_position; };
  inline vec3& Joint::direction() { return m_direction; };
  inline vec3& Joint::up() { return m_up; };
};

#endif
