#ifndef BODY_H
#define BODY_H

#include "config.h"

#include "libikengine.h"
#include "limb.h"
#include "joint.h"

#include <memory>
#include <vector>

#ifdef IKENGINE_OSG
# include <osg/ShapeDrawable>
# include <osg/PositionAttitudeTransform>
# include <osg/Geometry>
# include <osg/Geode>
#endif

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
        const vec3& position, const vec3& rotation, const vec3& servoAxis );
      std::shared_ptr<Joint> getAppendage( size_t i );
      void removeAppendage( size_t i );
      
      vec3& position();
      void position( const vec3& pos );
      vec3& rotation();
      void rotation( const vec3& rot );

#ifdef IKENGINE_OSG
      // Body provides the root of the robot for osg
      // Returns an osg::Group (Transform actually to allow for robot positioning/etc)
      // - Containing an osgDrawable for the body, with the gometry for the body within
      // - Each joint is another osg::Group, containing nothing (for now, might need a blob for the joing)
      // - In this group there is another Group for the Limb, which in turn can contain more Joints. The Limb's group also contains a Drawable for the Limb itself
      // Applications should just call createOsgGeometry on the Body, then updateOsgGeometry when needed
      // Applications should not call createOsgGeometry on the limbs/joints themselves, this might be hidden in the future

      // All geometry/nodes are created in this method, a fresh set is created every time
      osg::ref_ptr<osg::Group> createOsgGeometry();
      // Getter for the osg node
      osg::ref_ptr<osg::Group> osgGeometry() const;
      // Call to update the gometry for the robot's parameters
      void updateOsgGeometry();

    private:
      // For now hold references to all of these
      osg::ref_ptr<osg::PositionAttitudeTransform> m_osgTransform;
      osg::ref_ptr<osg::ShapeDrawable> m_osgDrawable;
      osg::ref_ptr<osg::Box> m_osgGeometry;
      osg::ref_ptr<osg::Geode> m_osgGeode;
#endif

    private:
      std::vector<std::shared_ptr<Joint>> m_appendages;
      vec3 m_dimensions;
      // Position in world space (center of body)
      vec3 m_position;
      // Rotation (radians (x,y,z))
      vec3 m_rotation;
  };
  
  inline vec3& Body::position() { return m_position; }
  inline void Body::position( const vec3& pos ) { m_position = pos; }
  inline vec3& Body::rotation() { return m_rotation; }
  inline void Body::rotation( const vec3& rot ) { m_rotation = rot; }
};

#endif
