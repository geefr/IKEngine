#ifndef CONTROLLER_DYNAMIXEL_H
#define CONTROLLER_DYNAMIXEL_H

#include "dynamixel_sdk.h"

/// Controller utility using libdxl
/// to drive Dynamixel servos
class Controller_Dynamixel
{
  public:
    Controller_Dynamixel( const std::string& deviceName );
    ~Controller_Dynamixel();

    bool valid() const;

    void setTorque( unsigned int servoID, bool enabled );
    void setServoAngle( unsigned int servoID, float angle );
    float getServoAngle( unsigned int servoID );
  private:
    int angleToPosition( float angle ) const;
    float positionToAngle( int position ) const;
    void dxlError(int result, uint8_t dxlCode) const;

    dynamixel::PortHandler* m_portHandler;
    dynamixel::PacketHandler* m_packetHandler;

    bool m_valid;
};

#endif
