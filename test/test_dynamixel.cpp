
#include "servos/servo_dynamixel.h"
#include "util/controller_dynamixel.h"
using namespace IKEngine;
using namespace IKEngine::Util;

#include <cmath>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
  std::string device{ "/dev/ttyUSB0" };
  if( argc >= 2 )
  {
    device = argv[1];
  }

  Controller_Dynamixel controller( device );
  if( !controller.valid() )
  {
    std::cout << "Failed to initialise dynamixel controller" << std::endl;
    return 1;
  }
  std::unique_ptr<Servo_Dynamixel> servo{ 
    new Servo_Dynamixel{ controller, 4 } };

  float minAngle{ -75.0 };
  float maxAngle{ -15.0 };
  float angle{ minAngle };
  bool increase{ true };
  while( true )
  {
    // Not setting the position so can't use any cached value
    //float angle{ servo->get( false ) };
    //angle *= (180.0/M_PI);
    //std::cout << "Servo angle: " << angle << std::endl;

    if( increase )
    {
      angle += 1.0;
      if( angle > maxAngle ) increase = false;
    }
    else
    {
      angle -= 1.0;
      if( angle < minAngle ) increase = true;
    }
    std::cout << "Setting Servo angle: " << angle << std::endl;
    servo->set( angle * (M_PI/180) );
    std::cout << "Read servo angle: " << servo->get(false) << std::endl;
  }

  return 0;
}
