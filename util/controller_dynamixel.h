#ifndef CONTROLLER_DYNAMIXEL_H
#define CONTROLLER_DYNAMIXEL_H

/// Controller utility using libdxl
/// to drive Dynamixel servos
class Controller_Dynamixel
{
  public:
    Controller_Dynamixel();
    ~Controller_Dynamixel();

    bool valid() const;

    void setServoAngle( unsigned int servoID, float angle );
    float getServoAngle( unsigned int servoID );
  private:
    bool m_valid;
};

#endif
