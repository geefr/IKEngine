
#include "controller_dynamixel.h"

#include "libdxl/dynamixel.h"

Controller_Dynamixel::Controller_Dynamixel()
: m_valid{ false }
{
  // TODO: Check what these do, this will only work
  // for the phex setup (dx12 servos, usb adapter)
  int baudNum{ 1 };
  int deviceIndex{ 0 };

  if( dxl_initialize(deviceIndex, baudNum ) != 0 )
  {
    return;
  }
  m_valid = true;
}

Controller_Dynamixel::~Controller_Dynamixel()
{
}

bool Controller_Dynamixel::valid() const
{
  return m_valid;
}

void Controller_Dynamixel::setServoAngle( unsigned int servoID, float angle )
{

}

float Controller_Dynamixel::getServoAngle( unsigned int servoID )
{
  return 0.0f;
}

