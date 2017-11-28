#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>

#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>

#include "body.h"
#include "joint.h"
#include "limb.h"

#include "servos/servo_mock.h"

int main()
{
    osgViewer::Viewer viewer;
    osg::Group* root = new osg::Group();
    
    // osgViewer defaults to z-up, IKEngine is y-up, with +ve z towards the camera
    // A rotation of (0,0,0) will point along the +ve z axis, so by default the camera
    // will look at the front of the robot
    
    // osg geometry returned from IKEngine will be adjusted as necesarry

    // Create a body
    // Position (x,y,z), y-up
    // Rotation (x,y,z), radians anticlockwise
    IKEngine::Body testBody( IKEngine::vec3(0.25, 0.125, 0.5) );
    testBody.position( IKEngine::vec3(0.0, 0.0, -1.0) );
    testBody.rotation( IKEngine::vec3(0.0, 0.0, 0.0) );
    
    // Single joint/limb
    // Servo rotation around y axis, relative to shoulder's rotation
    std::shared_ptr<IKEngine::Joint> shoulder{ new IKEngine::Joint( new IKEngine::Servo_Mock, IKEngine::vec3( 0.0, 1.0, 0.0 ) ) };
    // Limb pointing upwards from previous joint
    std::shared_ptr<IKEngine::Limb> arm{ new IKEngine::Limb( 2.0 ) };
    shoulder->next( arm );
    
    // Appendage, position, direction, 'up' vector
    // Appendage position is relative to the body
    // Sticking up out of the middle of the body, with direction of travel left/right as seen from 0,0,0
    
    // Test appendage
    // - Position is top/center of body
    // - Rotation axis is towards the camera (+ve rotation will wave limb to the right)
    testBody.addAppendage( shoulder, 
      IKEngine::vec3(0.0, 0.125 / 2.0, 0.0), 
      IKEngine::vec3(-osg::PI_2, 0.0, 0.0),
      IKEngine::vec3(0.0, 0.0, 1.0) );

    // Translate to osg geometry
    // If any limbs are added/removed we'll need to clear this and recreate
    root->addChild( testBody.createOsgGeometry() );


    osg::ref_ptr<osgGA::TrackballManipulator> manip{ new osgGA::TrackballManipulator() };
    osg::Quat eyeAttitude( 0.0, osg::X_AXIS,
                           0.0, osg::Y_AXIS,
                           0.0, osg::Z_AXIS );
    manip->setTransformation( osg::Vec3(0.0, 1.0, 0.0), eyeAttitude );
    
/*
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manip{ new osgGA::NodeTrackerManipulator() };
    manip->setTrackNode( testBody.osgGeometry() );
    manip->setTrackerMode( osgGA::NodeTrackerManipulator::TrackerMode::NODE_CENTER_AND_ROTATION );
    manip->setRotationMode( osgGA::NodeTrackerManipulator::RotationMode::ELEVATION_AZIM );
*/

    viewer.setSceneData( root );
    viewer.setCameraManipulator( manip );
    viewer.realize();

    while( !viewer.done() )
    {
      float servoAngle{ osg::DegreesToRadians(shoulder->servo().get()) };
      servoAngle += 0.1;
      shoulder->servo().set(servoAngle);
      
      testBody.rotation() = testBody.rotation() + IKEngine::vec3(0.0, 0.0, 0.0);
      testBody.updateOsgGeometry();
      
      viewer.frame();
    }

    return 0;
}
