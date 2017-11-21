
#include "servo_mock.h"


namespace IKEngine
{
	Servo_Mock::Servo_Mock( float angle )
	: m_angle{ angle }
	{}

	Servo_Mock::~Servo_Mock()
	{}

	void Servo_Mock::set( float angle )
	{
		m_angle = angle;
	}

	float Servo_Mock::get( bool allowCached )
	{
		// The mock servo angle is always cached as there's no hardware to read
		return m_angle;
	}
}
