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
       * For the moment bodies are cuboid
       */
      Body( const vec3& dimensions );
      ~Body();
      
      // TODO: Some form of solid geometry for the body
      // This will eventually be used for
      // - Collision detection to prevent robots hitting themselves
      // - Display in software/test applications before using hardware
      size_t numAppendages() const;
      void addAppendage( std::shared_ptr<Joint> appendage, 
        const vec3& position,
        const vec3& direction,
        const vec3& up );
      std::shared_ptr<Joint> getAppendage( size_t i );
      void removeAppendage( size_t i );

#ifdef IKENGINE_OSG
      osg::ref_ptr<osg::Drawable> osgGeometry() const;

    private:
      osg::ref_ptr<osg::Box> m_osgGeometry;
      osg::ref_ptr<osg::Drawable> m_osgDrawable;
#endif

    private:
      std::vector<std::shared_ptr<Joint>> m_appendages;
      vec3 m_dimensions;
  };
};

#endif
