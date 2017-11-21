
#include "controller_dynamixel.h"

#include <cmath>
#include <iostream>

#define ADDR_PRO_TORQUE_ENABLE 562
#define ADDR_PRO_GOAL_POSITION 596
#define ADDR_PRO_PRESENT_POSITION 611

#define PROTOCOL_VERSION 2.0

#define DXL_ID 1
#define BAUDRATE 1000000
#define DEVICENAME "/dev/ttyUSB0"

#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0
#define DXL_MINIMUM_POSITION_VALUE -150000
#define DXL_MAXIMUM_POSITION_VALUE  150000
#define DXL_MOVING_STATUS_THRESHOLD 20

// Default setting
#define DEFAULT_BAUDNUM         1 // 1Mbps
#define DEFAULT_ID              1 // ttyUSBX


namespace IKEngine
{
		
	Controller_Dynamixel::Controller_Dynamixel( const std::string& deviceName )
	: m_portHandler{ dynamixel::PortHandler::getPortHandler( deviceName.c_str() ) }
	, m_packetHandler{ dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION) }
	, m_valid{ false }
	{
		if (!m_portHandler->openPort())
		{
			return;
		}

		if (!m_portHandler->setBaudRate(BAUDRATE))
		{
			return;
		}


		m_valid = true;
	}

	Controller_Dynamixel::~Controller_Dynamixel()
	{
		m_portHandler->closePort();
	}

	bool Controller_Dynamixel::valid() const
	{
		return m_valid;
	}

	void Controller_Dynamixel::setTorque( unsigned int servoID, bool enabled )
	{
		// Enable torque
		uint8_t dxlCode{ 0x00 };
		int result = m_packetHandler->write1ByteTxRx(m_portHandler, servoID, ADDR_PRO_TORQUE_ENABLE, enabled ? TORQUE_ENABLE : TORQUE_DISABLE, &dxlCode);
		dxlError(result, dxlCode);
	}

	void Controller_Dynamixel::setServoAngle( unsigned int servoID, float angle )
	{
		int position{ angleToPosition(angle) };

		uint8_t dxlCode{ 0x00 };
		int result = m_packetHandler->write4ByteTxRx(m_portHandler, servoID, ADDR_PRO_GOAL_POSITION, position, &dxlCode);
		dxlError(result, dxlCode);
	}

	float Controller_Dynamixel::getServoAngle( unsigned int servoID )
	{
		// Position is an int
		int position{ 0 };
		uint8_t dxlCode{ 0x00 };
		// For reading it's read as a 4-byte block, so uint32_t*
		int result = m_packetHandler->read4ByteTxRx(m_portHandler, servoID, ADDR_PRO_PRESENT_POSITION, (uint32_t*)&position, &dxlCode);
		dxlError( result, dxlCode );
		
		//return positionToAngle( position );
		return (float)result;
	}

	int Controller_Dynamixel::angleToPosition( float angle ) const
	{
		return (int)( (angle + M_PI) * (360.0 / (float)(DXL_MAXIMUM_POSITION_VALUE - DXL_MINIMUM_POSITION_VALUE)) );
	}

	float Controller_Dynamixel::positionToAngle( int position ) const
	{
		return (float)( ((float)position * (float)(DXL_MAXIMUM_POSITION_VALUE - DXL_MINIMUM_POSITION_VALUE)) - M_PI);
	}

	void Controller_Dynamixel::dxlError(int result, uint8_t dxlCode) const
	{
		// TODO: Not sure if this is right
		// The original version using a deprecated method that spammed the terminal, this seems to print nothing
		if (result != COMM_SUCCESS)
		{
			std::cerr << m_packetHandler->getRxPacketError(dxlCode) << std::endl;
		}
		else if (dxlCode != 0)
		{
			m_packetHandler->printRxPacketError(dxlCode);
		}
	}
}
