
#ifndef BASICDEFINES_H_
#define BASICDEFINES_H_

// Types
typedef enum
{
	kEventErr, kEventNone, kEventOpened, kEventClosed
} EventType;
	
typedef enum
{
	kStateOpen, kStateClosed, kStateErr
} StateType;

typedef struct
{
	StateType state; 
	EventType event;
	bool enabled;
} ButtonEntry;

// Define the target platfomr we are building for. We need this
// because the hardware on Plyboy, WhamO-1 and WhamO-2 are 
// all different from one another
#define PLYBOY
//#define WHAMO1
//#define WHAMO2

#ifdef PLYBOY
#define NAME "Plyboy"
#define COLLECTOR_MOTOR_CONTROLLER Jaguar
#define INDEXER_MOTOR_CONTROLLER Jaguar
#define SHOOTER_MOTOR_CONTROLLER Jaguar
#define ARM_MOTOR_CONTROLLER Jaguar
#endif

#ifdef WHAMO1
#define NAME "WhamO-1"
#define COLLECTOR_MOTOR_CONTROLLER Jaguar
#define INDEXER_MOTOR_CONTROLLER Jaguar
#define SHOOTER_MOTOR_CONTROLLER Jaguar
#define ARM_MOTOR_CONTROLLER Jaguar
#endif

#ifdef WHAMO2
#define NAME "WhamO-2"
#define COLLECTOR_MOTOR_CONTROLLER Jaguar
#define INDEXER_MOTOR_CONTROLLER Jaguar
#define SHOOTER_MOTOR_CONTROLLER Jaguar
#define ARM_MOTOR_CONTROLLER Jaguar
#endif

// Digital IOs
#define LEFT_DRIVE_ENC_A 1
#define LEFT_DRIVE_ENC_B 2
#define RIGHT_DRIVE_ENC_A 3
#define RIGHT_DRIVE_ENC_B 4
#define CLAW_1_LOCK_SENSOR 5
#define CLAW_2_LOCK_SENSOR 6
#define INDEXER_SW 7
#define COMPRESSOR_PRESSURE_SW 8
#define UNUSED_DIO_9 9
#define UNUSED_DIO_10 10
#define UNUSED_DIO_11 11
#define UNUSED_DIO_12 12
#define UNUSED_DIO_13 13
#define UNUSED_DIO_14 14

// Analog Inputs
#define UNUSED_ANALOG_INPUT_1 1
#define UNUSED_ANALOG_INPUT_2 2
#define UNUSED_ANALOG_INPUT_3 3
#define UNUSED_ANALOG_INPUT_4 4
#define ARM_ROTATION_POT 5
#define UNUSED_ANALOG_INPUT_6 6
#define UNUSED_ANALOG_INPUT_7 7

// PWM Outputs
#define LEFT_DRIVE_PWM 1
#define UNUSED_PWM_OUTPUT_2 2
#define RIGHT_DRIVE_PWM 3
#define UNUSED_PWM_OUTPUT_4 4
#define ARM_PWM 5
#define UNUSED_PWM_OUTPUT_6 6
#define SHOOTER_PWM 7
#define PICKUP_PWM 8
#define UNUSED_PWM_OUTPUT_9 9
#define INDEX_PWM 10

// Joystick 1
#define UNUSED_BUTTON_1 1
#define UNUSED_BUTTON_2 2
#define UNUSED_BUTTON_3 3
#define UNUSED_BUTTON_4 4 
#define UNUSED_BUTTON_5 5
#define UNUSED_BUTTON_6 6
#define UNUSED_BUTTON_7 7
#define UNUSED_BUTTON_8 8
#define UNUSED_BUTTON_9 9
#define UNUSED_BUTTON_10 10
#define UNUSED_BUTTON_11 11

// Joystick 2
#define UNUSED_BUTTON_1 1
#define UNUSED_BUTTON_2 2
#define UNUSED_BUTTON_3 3
#define UNUSED_BUTTON_4 4 
#define UNUSED_BUTTON_5 5
#define UNUSED_BUTTON_6 6
#define BUTTON_SHIFT 7
#define UNUSED_BUTTON_8 8
#define UNUSED_BUTTON_9 9
#define UNUSED_BUTTON_10 10
#define UNUSED_BUTTON_11 11


// Gamepad Buttons
#define UNUSED_BUTTON_1 1
#define BUTTON_COLLECTOR_REV 2
#define BUTTON_SHOOTER 3
#define BUTTON_COLLECTOR_FWD 4
#define BUTTON_CLAW_1_LOCKED 5
#define BUTTON_CLAW_2_LOCKED 6
#define BUTTON_CLAW_1_UNLOCKED 7
#define BUTTON_CLAW_2_UNLOCKED 8
#define UNUSED_BUTTON_9 9
#define UNUSED_BUTTON_10 10
#define UNUSED_BUTTON_11 11
#define UNUSED_BUTTON_12 12


//Relays
#define INDEXER_SPIKE 1
#define COMPRESSOR_SPIKE 2
#define UNUSED_RELAY_3 4
#define UNUSED_RELAY_4 4
#define UNUSED_RELAY_5 5
#define UNUSED_RELAY_6 6
#define UNUSED_RELAY_7 7
#define UNUSED_RELAY_8 8

//Solenoid
#define SHIFTER_A 1
#define SHIFTER_B 2
#define CLAW_1_LOCKED 3
#define CLAW_1_UNLOCKED 4
#define CLAW_2_LOCKED 5
#define CLAW_2_UNLOCKED 6
#define UNUSED_SOLENOID_7 7
#define UNUSED_SOLENOID_8 8



#endif
