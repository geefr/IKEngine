
#include "joint.h"

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

};
