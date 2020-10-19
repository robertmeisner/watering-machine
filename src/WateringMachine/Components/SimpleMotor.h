/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef SimpleMotors_h
#include "StateMachineInterfaces/MotorStateMachine.h"
#define SimpleMotors_h
/**
 *
 */
class SimpleMotor : public MotorStateMachine
{
public:
	/**
	 * SimpleMotor
	 *
	 * @param  {bool(*)(int)} startFunc       : function used to start the device
	 * @param  {bool(*)()} stopFunc           : function used to stop the device
	 * @param  {bool(*)(int)} changeSpeedFunc : function used to change speed of the device
	 * @param  {bool(*)()=nullptr} initFunc   : function used for initiation of the device
	 * @param  {int} initialSpeed=100         : initial speed of the motor
	 */
	SimpleMotor(bool (*startFunc)(int), bool (*stopFunc)(), bool (*changeSpeedFunc)(int), bool (*initFunc)() = nullptr, unsigned long (*timeFunc)() = nullptr, int initialSpeed = 100);

	bool start(int speed = 100);
	bool stop();
	bool changeSpeed(int speed);
	unsigned long getDurationSinceLastChange();

	bool init();

protected:
	unsigned long (*_timeFunc)();
	bool (*_startFunc)(int);
	bool (*_stopFunc)();
	bool (*_changeSpeedFunc)(int);
	bool (*_initFunc)();
	int _speed = 0;
	unsigned long sinceLastChangeChrono;
};

#endif