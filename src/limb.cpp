
#include "limb.h"

namespace IKEngine
{
  Limb::Limb( float length, const vec3& limbVector )
  : m_length{ length }
  , m_limbVector{ limbVector }
  {
    m_limbVector.normalize();
  }
  
  Limb::~Limb()
  {
    
  }

};
