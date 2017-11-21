#ifndef SERVO_MOCK_H
#define SERVO_MOCK_H

#include "servo.h"


namespace IKEngine
{
	/**
	 * A mock servo for testing purposes
	 */
	class Servo_Mock : public Servo
	{
		public:
			Servo_Mock( float angle = 0.0f );
			virtual ~Servo_Mock();

			virtual void set( float angle );
			virtual float get( bool allowCached );

		private:
			// Last set angle
			float m_angle;
	};
}

#endif
