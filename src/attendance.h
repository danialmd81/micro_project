#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <stdlib.h>

#include "attendance.h"
#include "buzzer.h"
#include "eeprom.h"
#include "keypad.h"
#include "lcd.h"
#include "temperature.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"

void attendanceInitialization();
void studentManagement();
void viewPresentStudents();
void temperatureMonitoring();
void retrieveStudentData();
void trafficMonitoring();
void removeStudent();

#endif // ATTENDANCE_H