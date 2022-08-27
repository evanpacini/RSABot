// Motor pins
#define MOTOR_1REV 7 // left
#define MOTOR_1EN 24
#define MOTOR_1FWD 6
#define MOTOR_2REV 3 // right
#define MOTOR_2EN 25
#define MOTOR_2FWD 2

// Sensor Connection
#define TCRT500_LEFT 8
#define TCRT500_RIGHT 9

// Speeds
#define MAX_SPEED 100
#define TURNING_SPEED 100

// Delays
#define TURN_DELAY 25
#define FWD_DELAY 10

uint8_t leftSensorState;
bool rightSensorState;

void setup()
{
    // Sensor setup
    pinMode(TCRT500_LEFT, INPUT);
    pinMode(TCRT500_RIGHT, INPUT);

    // Motor Setup
    pinMode(MOTOR_1REV, OUTPUT); // left
    pinMode(MOTOR_1EN, OUTPUT);
    pinMode(MOTOR_1FWD, OUTPUT);
    pinMode(MOTOR_2REV, OUTPUT); // right
    pinMode(MOTOR_2EN, OUTPUT);
    pinMode(MOTOR_2FWD, OUTPUT);

    // Start motors
    digitalWrite(MOTOR_1EN, HIGH);
    digitalWrite(MOTOR_2EN, HIGH);
    delay(500);
}

void loop()
{
    leftSensorState = digitalRead(TCRT500_LEFT);
    rightSensorState = digitalRead(TCRT500_RIGHT);
    Serial.println(leftSensorState);
    Serial.println(rightSensorState);

    if (rightSensorState && leftSensorState)
    {
        // forward
        analogWrite(MOTOR_1REV, 0);
        analogWrite(MOTOR_2REV, 0);
        analogWrite(MOTOR_1FWD, MAX_SPEED);
        analogWrite(MOTOR_2FWD, MAX_SPEED);
        // delay(FWD_DELAY);
    }

    if (rightSensorState && !leftSensorState)
    {
        // turn left
        analogWrite(MOTOR_1REV, 0);
        analogWrite(MOTOR_2FWD, 0);
        analogWrite(MOTOR_2REV, 0);
        analogWrite(MOTOR_1FWD, TURNING_SPEED);
        // delay(TURN_DELAY);
    }

    if (!rightSensorState && leftSensorState)
    {
        // turn right
        analogWrite(MOTOR_1FWD, 0);
        analogWrite(MOTOR_2REV, 0);
        analogWrite(MOTOR_1REV, 0);
        analogWrite(MOTOR_2FWD, TURNING_SPEED);
        // delay(TURN_DELAY);
    }

    if (!rightSensorState && !leftSensorState)
    {
        // stop
        analogWrite(MOTOR_1FWD, 0);
        analogWrite(MOTOR_1REV, 0);
        analogWrite(MOTOR_2FWD, 0);
        analogWrite(MOTOR_2REV, 0);
        // delay(FWD_DELAY);
    }
}
