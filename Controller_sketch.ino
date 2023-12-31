#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

void messageCallback(const std_msgs::String& msg){
  const char* action = msg.data.c_str();
}

ros::Subscriber<std_msgs::String> sub("input_daf", &messageCallback );

const int motor1IN1 = 11;
const int motor1IN2 = 9;
const int motor1PWM = 13;
const int motor2IN1 = 10;
const int motor2IN2 = 8;
const int motor2PWM = 12;

int pwm = 140;
int pwm1 = 84;
int pwm2 = 84;
float offset = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(57600);

  pinMode(motor1IN1, OUTPUT);
  pinMode(motor1IN2, OUTPUT);
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor2IN1, OUTPUT);
  pinMode(motor2IN2, OUTPUT);
  pinMode(motor2PWM, OUTPUT);

  // Connect to ROS
  nh.initNode();
  nh.subscribe(sub);

  // Other setup code
}

void goRight() {

  digitalWrite(motor1PWM, 120);
  digitalWrite(motor1IN1, HIGH);
  digitalWrite(motor1IN2, LOW);

  digitalWrite(motor2PWM, 0);
  digitalWrite(motor2IN1, HIGH);
  digitalWrite(motor2IN2, LOW);

}


void goLeft() {

  digitalWrite(motor1PWM, 0);
  digitalWrite(motor1IN1, HIGH);
  digitalWrite(motor1IN2, LOW);

  digitalWrite(motor2PWM, 120);
  digitalWrite(motor2IN1, HIGH);
  digitalWrite(motor2IN2, LOW);

}


void goForward() {

  digitalWrite(motor1IN1, HIGH);
  digitalWrite(motor1IN2, LOW);
  analogWrite(motor1PWM, pwm);
  digitalWrite(motor2IN1, HIGH);
  digitalWrite(motor2IN2, LOW);
  analogWrite(motor2PWM, pwm);

}

void stopMoving() {
  digitalWrite(motor1IN1, LOW);
  digitalWrite(motor1IN2, LOW);
  analogWrite(motor1PWM, 0);
  
  digitalWrite(motor2IN1, LOW);
  digitalWrite(motor2IN2, LOW);
  analogWrite(motor2PWM, 0);
}

void loop() {
  nh.spinOnce();

  Serial.println(action);

  if (strcmp(action, "Go") == 0) {
    goForward();
  } else if (strcmp(action, "Left") == 0) {
    goLeft();
  } else if (strcmp(action, "Right") == 0) {
    goRight();
  } else {
    stopMoving();
  }
}
