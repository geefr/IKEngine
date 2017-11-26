#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

#include "body.h"
#include "joint.h"
#include "limb.h"

#include "servos/servo_mock.h"

int main()
{
    osgViewer::Viewer viewer;
    osg::Group* root = new osg::Group();

    // Create a body
    IKEngine::Body testBody( IKEngine::vec3(0.25, 0.125, 0.5) );
    
    // Single joint/limb
    {
      std::shared_ptr<IKEngine::Joint> shoulder{ new IKEngine::Joint( new IKEngine::Servo_Mock ) };
      std::shared_ptr<IKEngine::Limb> arm{ new IKEngine::Limb( 10.0 ) };
      shoulder->next( arm );
      
      // Appendage, position, direction, 'up' vector
      // Appendage position is relative to the body
      // Sticking up out of the middle of the body, with direction of travel left/right as seen from 0,0,0
      testBody.addAppendage( shoulder, IKEngine::vec3(0.0, 0.125, 0.0), IKEngine::vec3(0.0, 1.0, 0.0), IKEngine::vec3(0.0, 0.0, 1.0) );
    }

    // Translate to osg geometry
    // If any limbs are added/removed we'll need to clear this and recreate
    root->addChild( testBody.createOsgGeometry() );

    // switch off lighting as we haven't assigned any normals
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    //The final step is to set up and enter a simulation loop
    viewer.setSceneData( root );

    //viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();

    while( !viewer.done() )
    {
        viewer.frame();
    }

    return 0;
}
