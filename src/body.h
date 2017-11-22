#ifndef BODY_H
#define BODY_H

#include "config.h"

#include "libikengine.h"
#include "limb.h"
#include "joint.h"

#include <memory>
#include <vector>

namespace IKEngine
{
  /**
   * A Body consists of some form of solid geometry
   * and a set of appendages
   * An appendage always starts with a Joing and ends
   * with a Limb
   */
  class Body
  {
    public:
      /**
       * Constructor
       * 
       */
      Body();
      ~Body();
      
      // TODO: Some form of solid geometry for the body
      // This will eventually be used for
      // - Collision detection to prevent robots hitting themselves
      // - Display in software/test applications before using hardware
      
      std::vector<std::shared_ptr<Joint>> m_appendages;
  };
};

#endif
