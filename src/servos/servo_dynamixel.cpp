
#include "servo_dynamixel.h"
    
Servo_Dynamixel::Servo_Dynamixel( Controller_Dynamixel& controller, unsigned int servoID, float angle )
: m_controller( controller )
, m_id{ servoID }
, m_angle{ angle }
{
  set( m_angle );
}

Servo_Dynamixel::~Servo_Dynamixel()
{

}

void Servo_Dynamixel::set( float angle )
{
  m_angle = angle;
  m_controller.setServoAngle( m_id, angle );
}

float Servo_Dynamixel::get( bool allowCached )
{
  if( allowCached )
  {
    return m_angle;
  }
  return m_controller.getServoAngle( m_id );
}
