#ifndef SERVO_H
#define SERVO_H


namespace IKEngine
{
		
	/**
	 * The base class for all servos
	 * 
	 * The angle of a servo is defined relative to the zero point
	 * by default this is pointing straight away from the servo
	 * e.g 
	 * -----
	 * |   ->
	 * -----
	 *
	 * Angles range from -PI (anticlockwise) to PI (clockwise)
	 * How this relates to the servo is up to the child implementation
	 * 
	 * A servo can specify a minimum and maximum allowed angle
	 * A servo cannot specify an angle offset (Future enhancement)
	 * so for now it's up to the Servo implementation to calculate
	 * anything specific to the hardware
	 *
	 */
	class Servo
	{
		public:
			enum class Type
			{
				/// Dynamixel servos
				Dynamixel
			};  

		/**
		 * Set the servo to the specified angle
		 *
		 * @param angle Angle in radians, +ve clockwise from the zero point
		 */
		virtual void set( float angle ) = 0;
		
		/**
		 * Get the angle of the servo
		 * @param allowCached If true the servo may return a cached value. If false the servo should read the position from hardware if at all possible.
		 */
		virtual float get( bool allowCached = true ) = 0;

		virtual ~Servo();

		Servo();
	};

	inline Servo::Servo()
	{
	}

	inline Servo::~Servo()
	{
	}
}

#endif
