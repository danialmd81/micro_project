#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <stdlib.h>

#include "attendance.h"
#include "buzzer.h"
#include "eeprom.h"
#include "glcd.h"
#include "keypad.h"
#include "temperature.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"
#include "Timer.h"

#define TIME_LIMIT_SECOND 15*60 // 15 minutes

void submitStudentCode();
void studentManagement();
void viewPresentStudents();
void temperatureMonitoring();
void retrieveStudentData();
void trafficMonitoring();
void removeStudent();

#endif // ATTENDANCE_H