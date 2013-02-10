#include "WPILib.h"
#include "BasicDefines.h"
#include "EGamepad.h"
#include "EAnalogTrigger.h"
#include "EDigitalInput.h"
#include "Ejoystick.h"

class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; 
	EJoystick stick2;
	EGamepad gamepad; //gamepad
	Talon collectorMotor;
	Talon armMotor;
	DoubleSolenoid shifter;
	DoubleSolenoid claw1;
	DoubleSolenoid claw2;
	Compressor compressor;
	AnalogChannel potentiometer;
	Talon motorController;
	EDigitalInput index_switch;
	Jaguar indexer;
	Jaguar shooter;
	
	bool m_collectorMotorRunning;
	bool m_shooterMotorRunning;
	DriverStationLCD *dsLCD;

public:
	RobotDemo(void):
		myRobot(LEFT_DRIVE_VICTOR, RIGHT_DRIVE_VICTOR),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		stick2(2),
		gamepad(3),
		collectorMotor(PICKUP_JAG),
		armMotor(ARM_TALON),
		shifter(SHIFTER_A,SHIFTER_B),
		claw1(CLAW_1_LOCKED, CLAW_1_UNLOCKED),
		claw2(CLAW_2_LOCKED, CLAW_2_UNLOCKED),
		compressor(COMPRESSOR_PRESSURE_SW, COMPRESSOR_SPIKE),
		potentiometer(ARM_ROTATION_POT),
		motorController(6),
		index_switch(INDEXER_SW),
		indexer(INDEX_JAG),
		shooter(SHOOTER_JAG)
	{
		m_collectorMotorRunning = false;
		m_shooterMotorRunning = false;
		dsLCD = DriverStationLCD::GetInstance();
		dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "Celina " __TIME__);
		dsLCD->UpdateLCD();
		myRobot.SetExpiration(0.1);
		shifter.Set(DoubleSolenoid::kReverse);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}
	
	void HandleDriverInputsManual(void)
	{
		myRobot.ArcadeDrive(stick);
		if(kEventClosed == stick2.GetEvent(BUTTON_SHIFT))
		{
			// Shift into high gear.
			shifter.Set(DoubleSolenoid::kForward);
		}
		else if(kEventOpened == stick2.GetEvent(BUTTON_SHIFT))
		{
			// Shift into low gear.
			shifter.Set(DoubleSolenoid::kReverse);
		}
	}
	// Shifts the super shifters into high gear if using manual transmission.

	void HandleDriverInputsAutomatic(void)
	{
		//myRobot.ArcadeDrive(stick);
		
		if(DoubleSolenoid::kReverse == shifter.Get())
		{
			if(stick.GetY() < -0.25)
			{
				shifter.Set(DoubleSolenoid::kForward);
			}
		}
		// If the robot is in low gear and is over 0.2 input,
		// then switch into high gear.
		else if(stick.GetY() > -0.2)
		{
			shifter.Set(DoubleSolenoid::kReverse);
		}
		
		SquareInputs();
	}
	
	void SquareInputs(void)
	{
		if(stick.GetY() < 0)
		{
			if(DoubleSolenoid::kReverse == shifter.Get())
			{
				motorController.Set((stick.GetY() * stick.GetY()) * -4.0);
			}
			else if(DoubleSolenoid::kForward == shifter.Get())
			{
				motorController.Set((stick.GetY() * stick.GetY()) * -1.0);
			}
		}
		else if(stick.GetY() > 0)
		{
			if(DoubleSolenoid::kReverse == shifter.Get())
			{
				motorController.Set((stick.GetY() * stick.GetY()) * 4.0);
			}
			else if(DoubleSolenoid::kForward == shifter.Get())
			{
				motorController.Set(stick.GetY() * stick.GetY());
			}
		}
	}
	
	void HandleArmInputs(void)
	{
		if (gamepad.GetLeftY() < -0.1)
		{
			if (potentiometer.GetVoltage() < 4.5)
			{
				armMotor.Set(1.0);
			}
			else
			{
				armMotor.Set(0.0);
			}
		}
		else if (gamepad.GetLeftY() > 0.1)
		{
			if (potentiometer.GetVoltage() > .5)
			{
				armMotor.Set(-1.0);
			}
			else
			{
				armMotor.Set(0.0);
			}	
		}
		else
		{
			armMotor.Set(0.0);
		}
		
		if (gamepad.GetEvent(BUTTON_CLAW_1_LOCKED) == kEventClosed)
		{
			claw1.Set(DoubleSolenoid::kForward);
		}
		else if (gamepad.GetEvent(BUTTON_CLAW_1_UNLOCKED) == kEventClosed)
		{
			claw1.Set(DoubleSolenoid::kReverse);
		}
		else if (gamepad.GetEvent(BUTTON_CLAW_2_LOCKED) == kEventClosed)
		{
			claw2.Set(DoubleSolenoid::kForward);
		}
		else if (gamepad.GetEvent(BUTTON_CLAW_2_UNLOCKED) == kEventClosed)
		{
			claw2.Set(DoubleSolenoid::kReverse);
		}
	}
	
	void HandleCollectorInputs ()
	{		
		dsLCD->PrintfLine(DriverStationLCD::kUser_Line4, "SMR %d", m_shooterMotorRunning);
		if (false == m_shooterMotorRunning)
		{
			dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, " In SMR");

			if (kEventClosed == gamepad.GetEvent(BUTTON_COLLECTOR_FWD))
			{
				dsLCD->PrintfLine(DriverStationLCD::kUser_Line6, " READ BUTTON");

					collectorMotor.Set(1.0);
					m_collectorMotorRunning = true;
			}
			else if (kEventOpened == gamepad.GetEvent(BUTTON_COLLECTOR_FWD))
			{
				collectorMotor.Set(0.0);
				m_collectorMotorRunning = false;
			}
			else if (kEventClosed == gamepad.GetEvent(BUTTON_COLLECTOR_REV))
			{
				collectorMotor.Set(-1.0);
				m_collectorMotorRunning = true;
			}
			else if (kEventOpened == gamepad.GetEvent(BUTTON_COLLECTOR_REV))
			{
				collectorMotor.Set(0.0);
				m_collectorMotorRunning = false;
			}
		}
	}
	void HandleShooterInputs()
	{	
		dsLCD->PrintfLine(DriverStationLCD::kUser_Line5, " CMR %d SMR %d", m_collectorMotorRunning, m_shooterMotorRunning);
		if (!m_collectorMotorRunning && !m_shooterMotorRunning)
		{
			if (kEventClosed == gamepad.GetEvent(BUTTON_SHOOTER))
			{
				shooter.Set(-0.5);
				indexer.Set(-0.5);
				m_shooterMotorRunning  = true;
			}
		}
		else	
		{
			if (index_switch.GetEvent() == kEventClosed)
			{
				indexer.Set(0.0);
				shooter.Set(0.0);
				m_shooterMotorRunning  = false;

			}
		}		
	}

	void OperatorControl(void)
	{
		myRobot.SetSafetyEnabled(true);
		
		gamepad.EnableButton(BUTTON_COLLECTOR_FWD);
		gamepad.EnableButton(BUTTON_COLLECTOR_REV);
		gamepad.EnableButton(BUTTON_SHOOTER);
		gamepad.EnableButton(BUTTON_CLAW_1_LOCKED);
		gamepad.EnableButton(BUTTON_CLAW_2_LOCKED);
		gamepad.EnableButton(BUTTON_CLAW_1_UNLOCKED);
		gamepad.EnableButton(BUTTON_CLAW_2_UNLOCKED);
		gamepad.Update();
		
		index_switch.Update();
		
		stick2.EnableButton(BUTTON_SHIFT);
		stick2.Update();
		
		claw1.Set(DoubleSolenoid::kReverse);
		claw2.Set(DoubleSolenoid::kReverse);

		compressor.Start ();
		
		while (IsOperatorControl())
		{
			gamepad.Update();
			stick2.Update();
			index_switch.Update();
			//myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			HandleCollectorInputs();
			HandleDriverInputsManual();
			HandleArmInputs();
			HandleShooterInputs();
			dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Voltage: %f", potentiometer.GetVoltage());
			dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "Input: %f", motorController.Get());
			dsLCD->UpdateLCD();
			Wait(0.005);				// wait for a motor update time
		}
	}
	/**
	 * Runs during test mode
	 */
	void Test() 
	{
	}
};

START_ROBOT_CLASS(RobotDemo);

