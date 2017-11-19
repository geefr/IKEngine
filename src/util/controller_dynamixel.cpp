
#include "controller_dynamixel.h"

#include "libdxl/dynamixel.h"

#include <cmath>
#include <iostream>

// Servo settings
// Control table address
#define P_GOAL_POSITION_L       30
#define P_GOAL_POSITION_H       31
#define P_GOAL_SPEED_L          32
#define P_GOAL_SPEED_H          33
#define P_PRESENT_POSITION_L    36
#define P_PRESENT_POSITION_H    37
#define P_MOVING                46

// Default setting
#define DEFAULT_BAUDNUM         1 // 1Mbps
#define DEFAULT_ID              1 // ttyUSBX

Controller_Dynamixel::Controller_Dynamixel()
: m_valid{ false }
{
  // TODO: Check what these do, this will only work
  // for the phex setup (dx12 servos, usb adapter)
  int baudNum{ DEFAULT_BAUDNUM };
  int deviceIndex{ DEFAULT_ID };

  if( dxl_initialize(deviceIndex, baudNum ) == 0 )
  {
    return;
  }
  m_valid = true;
}

Controller_Dynamixel::~Controller_Dynamixel()
{
  dxl_terminate();
}

bool Controller_Dynamixel::valid() const
{
  return m_valid;
}

void Controller_Dynamixel::setServoAngle( unsigned int servoID, float angle )
{
  int position{ angleToPosition(angle) };
  dxl_write_word( servoID, P_GOAL_POSITION_L, position );
  dxlError();
}

float Controller_Dynamixel::getServoAngle( unsigned int servoID )
{
  int position{ dxl_read_word( servoID, P_PRESENT_POSITION_L ) };
  dxlError();

  return positionToAngle( position );
}

int Controller_Dynamixel::angleToPosition( float angle ) const
{
  // Ensure angle is positive
  angle += M_PI;

  // Servo position is 0 -> 1024
  // 0 -> 4096 for EX series
  return (int)(1024.0f / angle);
}

float Controller_Dynamixel::positionToAngle( int position ) const
{
  float angle( position * ((2 * M_PI)/1024) );
  return angle - M_PI;
}

void Controller_Dynamixel::dxlError() const
{
return;
  switch( dxl_get_result() )
  {
    case COMM_TXSUCCESS:
      break;
    case COMM_RXSUCCESS:
      break;
    case COMM_TXFAIL:
      std::cerr << "Controller_Dynamixel: COMM_TXFAIL" << std::endl;
      break;
    case COMM_RXFAIL:
      std::cerr << "Controller_Dynamixel: COMM_RXFAIL" << std::endl;
      break;
    case COMM_TXERROR:
      std::cerr << "Controller_Dynamixel: COMM_TXERROR" << std::endl;
      break;
    case COMM_RXWAITING:
      std::cerr << "Controller_Dynamixel: COMM_RXWAITING" << std::endl;
      break;
    case COMM_RXTIMEOUT:
      std::cerr << "Controller_Dynamixel: COMM_RXTIMEOUT" << std::endl;
      break;
    case COMM_RXCORRUPT:
      std::cerr << "Controller_Dynamixel: COMM_RXCORRUPT" << std::endl;
      break;
  }
}
