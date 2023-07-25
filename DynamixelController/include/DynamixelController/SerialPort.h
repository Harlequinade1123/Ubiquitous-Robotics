#pragma once

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class SerialPort
{
 public:
  SerialPort();
  ~SerialPort();
  void writeCommand(std::string command);
  void openSerial(const char *device_name, int baudrate_int);
  void closeSerial();
  bool tryConvertingBaudrate(unsigned int &BAUDRATE, int baudrate_int);

 private:
  int file_descriptor;
  bool port_is_open;
};