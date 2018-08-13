#include "PID.h"

// using namespace std;

/*
 * TODO: Complete the PID class.
 */

PID::PID() {
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;

  prev_cte = 0.0;

  Kp = 0.0;
  Ki = 0.0;
  Kd = 0.0;

  counter = 0;
  errorSum = 0.0;
}

PID::~PID() {
}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}

void PID::UpdateError(double cte) {
  // Proportional error
  p_error = cte;

  // Integral error
  i_error += cte;

  // Differential error
  d_error = cte - prev_cte;

  prev_cte = cte;

  errorSum += cte;
  counter++;
}

double PID::TotalError() {
  return -p_error * Kp - i_error * Ki - d_error * Kd;
}

