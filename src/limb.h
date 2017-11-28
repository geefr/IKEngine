#ifndef LIMB_H
#define LIMB_H

#include "config.h"

#include "libikengine.h"

#include <memory>


#ifdef IKENGINE_OSG
# include <osg/Geometry>
# include <osg/Transform>
# include <osg/Geode>
#endif


namespace IKEngine
{
  class Joint;
  
  /**
   * A Limb connecting 1 or more joints
   * 'Back' joint is the joint before this limb
   * 'Front' joint is the joint after this limb
   */
  class Limb
  {
    public:
      /**
       * Constructor
       * 
       * @param length Length of the limb
       * @param limbVector Direction vector of the limb relative to parent joint
       */
      Limb( float length, const vec3& limbVector = { 0.0, 0.0, 1.0 } );
      ~Limb();
      
      std::shared_ptr<Joint> backJoint() const;
      std::shared_ptr<Joint> frontJoint() const;
      
      void backJoint( std::shared_ptr<Joint> joint );
      void frontJoint( std::shared_ptr<Joint> joint );
      
      /**
       * Get the direction vector of this limb
       * Vector points from backJoint -> frontJoint
       */
      const vec3& limbVector() const;
     
#ifdef IKENGINE_OSG
      // All geometry/nodes are created in this method, a fresh set is created every time
      osg::ref_ptr<osg::Group> createOsgGeometry();
      // Getter for the osg node
      osg::ref_ptr<osg::Group> osgGeometry() const;
      // Call to update the gometry for the robot's parameters
      void updateOsgGeometry();

    private:
      // For now hold references to all of these
      osg::ref_ptr<osg::Transform> m_osgTransform;
      osg::ref_ptr<osg::Geode> m_osgGeode;
      osg::ref_ptr<osg::Geometry> m_osgGeometry;
#endif

    private:
      std::shared_ptr<Joint> m_backJoint;
      std::shared_ptr<Joint> m_frontJoint;
      float m_length;
      vec3 m_limbVector;
  };
    
  inline std::shared_ptr<Joint> Limb::backJoint() const
  {
    return m_backJoint;
  }
  
  inline std::shared_ptr<Joint> Limb::frontJoint() const
  {
    return m_frontJoint;
  }
  
  inline void Limb::backJoint( std::shared_ptr<Joint> joint )
  {
    m_backJoint = joint;
  }
  
  inline void Limb::frontJoint( std::shared_ptr<Joint> joint )
  {
    m_frontJoint = joint;
  }
  
  inline const vec3& Limb::limbVector() const
  {
    return m_limbVector;
  }
  
};

#endif
