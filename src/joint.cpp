
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

  std::shared_ptr<Limb> Joint::next() const
  {
    return m_next;
  }

  void Joint::next( std::shared_ptr<Limb> l )
  {
    m_next = l;
  }
};
