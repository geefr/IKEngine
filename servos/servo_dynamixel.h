#ifndef SERVO_DYNAMIXEL_H
#define SERVO_DYNAMIXEL_H

#include "servo.h"
#include "util/controller_dynamixel.h"

class Servo_Dynamixel : public Servo
{
  public:
    Servo_Dynamixel( Controller_Dynamixel& controller, unsigned int servoID, float angle = 0.0f );
    virtual ~Servo_Dynamixel();

    virtual void set( float angle );
    virtual float get( bool allowCached = true );

  private:
    Controller_Dynamixel& m_controller;
    // Servo ID
    unsigned int m_id;
    // Last set angle
    float m_angle;
};

#endif
