#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "ddr.h"
#include "eeprom.h"
#include "lcd.h"

void attendanceInitialization();
void studentManagement();
void viewPresentStudents();
void temperatureMonitoring();
void retrieveStudentData();
void trafficMonitoring();

#endif // ATTENDANCE_H