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
#include "limb.h"

int main()
{
    osgViewer::Viewer viewer;
    osg::Group* root = new osg::Group();

    osg::ref_ptr<osg::Geode> roboGeode{ new osg::Geode() };
    root->addChild( roboGeode );

    // Create a body
    IKEngine::Body testBody( IKEngine::vec3(3.0, 2.0, 1.0) );
    roboGeode->addDrawable( testBody.osgGeometry() );

    // Single joint/limb
    {
      std::shared_ptr<Joint> shoulder{ new Joint( new Servo_Mock ) };
      std::shared_ptr<Limb> arm{ new Limb( 10.0 ) };
      shoulder->next( arm );
      testBody->addAppendage( shoulder, IKEngine::vec3(0.0, 0.0, 1.0), IKEngine::vec3(0.0, 1.0, 0.0) );
    }


    // Create a limb
    //IKEngine::Limb testLimb( 10.0, IKEngine::vec3(0.0, 0.0, 1.0) );
    //osg::ref_ptr<osg::Geometry> limbGeom( testLimb.osgGeometry() );
    //roboGeode->addDrawable(limbGeom);

    // switch off lighting as we haven't assigned any normals
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    //The final step is to set up and enter a simulation loop
    viewer.setSceneData( root );

    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();

    while( !viewer.done() )
    {
        viewer.frame();
    }

    return 0;
}
