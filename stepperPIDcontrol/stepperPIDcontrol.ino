#include "SingleEMAFilterLib.h"
#include <CheapStepper.h>
#include <PID_v1.h>

SingleEMAFilter<int> singleEMAFilter1(0.1);
SingleEMAFilter<int> singleEMAFilter2(0.1);

double Setpoint, Input, Output;
double Kp=0.1, Ki=0.015, Kd=0.003;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

CheapStepper stepper (22,23,24,25); 

int contador=0;

void setup() {
  stepper.setRpm(20); 
  Serial.begin(9600); 
  Input = 0;
  Setpoint = 0;
  myPID.SetOutputLimits(-180, 180);
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  Input=(double)analogRead(A0);
  Setpoint=(double)singleEMAFilter2.AddValue(analogRead(A1));
  myPID.Compute();
    if (Output>=0){
      stepper.moveDegrees (LOW,(int)Output);
    }else{
      stepper.moveDegrees (HIGH,(int)-Output);
    }
    Serial.print(Setpoint);
    Serial.print(",\t");
    Serial.println(Input);  
}

