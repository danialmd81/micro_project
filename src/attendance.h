#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <stdlib.h>

#include "Timer.h"
#include "attendance.h"
#include "buzzer.h"
#include "eeprom.h"
#include "glcd.h"
#include "keypad.h"
#include "temperature.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"

// #define TIME_LIMIT_SECOND 15*60 // 15 minutes
#define TIME_LIMIT_SECOND 15 // 15 Seconds

void submitStudentCode();
void studentManagement();
void viewPresentStudents();
void temperatureMonitoring();
void retrieveStudentData();
void trafficMonitoring();
void removeStudent();

#endif // ATTENDANCE_H