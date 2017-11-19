#ifndef JOINT_H
#define JOINT_H

#include "libikengine.h"
#include "servos/servo.h"

#include <memory>

namespace IKEngine
{
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
      
    private:
      float m_degreeOffset;
      std::unique_ptr<Servo> m_servo;
  };
};

#endif
