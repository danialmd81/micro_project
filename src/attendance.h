#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "attendance.h"
#include "buzzer.h"
#include "ddr.h"
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