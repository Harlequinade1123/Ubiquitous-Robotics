#include "SerialPort.h"

SerialPort::SerialPort()
{
  file_descriptor = 0;
  port_is_open    = false;
}

SerialPort::~SerialPort() {}

void SerialPort::writeCommand(std::string command)
{
  if (!port_is_open)
  {
    printf("Port is not open\n");
    return;
  }
  int rec = write(file_descriptor, command.c_str(), command.size());
  if(rec < 0)
  {
    printf("Write Error\n");
  }
}

void SerialPort::openSerial(const char *device_name, int baudrate_int)
{
  file_descriptor = open(device_name, O_RDWR);
  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;

  // Read in existing settings, and handle any error
  if(tcgetattr(file_descriptor, &tty) != 0)
  {
    printf("Serial Failed 1: %s\n", device_name);
  }

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 0;
  tty.c_cc[VMIN]  = 0;

  // Set in/out baud rate
  unsigned int BAUDRATE;
  if (tryConvertingBaudrate(BAUDRATE, baudrate_int) == false)
  {
      printf("Invalid BAUDRATE : %s\n", device_name);
  }
  cfsetispeed(&tty, BAUDRATE);
  cfsetospeed(&tty, BAUDRATE);

  // Save tty settings, also checking for error
  if (tcsetattr(file_descriptor, TCSANOW, &tty) != 0)
  {
    printf("Serial Failed 2: %s\n", device_name);
  }

  if (file_descriptor < 0)
  {
    printf("Serial Failed 0: %s\n", device_name);
  }
  else
  {
    printf("Serial Open : %s\n", device_name);
    port_is_open = true;
  }
}

void SerialPort::closeSerial()
{
  if (!port_is_open)
  {
    printf("Port is not open\n");
    return;
  }
  close(file_descriptor);
  printf("Serial Close");
  port_is_open = false;
}

bool SerialPort::tryConvertingBaudrate(unsigned int &BAUDRATE, int baudrate_int)
{
  switch(baudrate_int)
  {
    case 0       : BAUDRATE = B0;       break;
    case 50      : BAUDRATE = B50;      break;
    case 75      : BAUDRATE = B75;      break;
    case 110     : BAUDRATE = B110;     break;
    case 134     : BAUDRATE = B134;     break;
    case 150     : BAUDRATE = B150;     break;
    case 200     : BAUDRATE = B200;     break;
    case 300     : BAUDRATE = B300;     break;
    case 600     : BAUDRATE = B600;     break;
    case 1200    : BAUDRATE = B1200;    break;
    case 1800    : BAUDRATE = B1800;    break;
    case 2400    : BAUDRATE = B2400;    break;
    case 4800    : BAUDRATE = B4800;    break;
    case 9600    : BAUDRATE = B9600;    break;
    case 19200   : BAUDRATE = B19200;   break;
    case 38400   : BAUDRATE = B38400;   break;
    case 57600   : BAUDRATE = B57600;   break;
    case 115200  : BAUDRATE = B115200;  break;
    case 230400  : BAUDRATE = B230400;  break;
    case 460800  : BAUDRATE = B460800;  break;
    case 500000  : BAUDRATE = B500000;  break;
    case 576000  : BAUDRATE = B576000;  break;
    case 921600  : BAUDRATE = B921600;  break;
    case 1000000 : BAUDRATE = B1000000; break;
    case 1152000 : BAUDRATE = B1152000; break;
    case 1500000 : BAUDRATE = B1500000; break;
    case 2000000 : BAUDRATE = B2000000; break;
    case 2500000 : BAUDRATE = B2500000; break;
    case 3000000 : BAUDRATE = B3000000; break;
    case 3500000 : BAUDRATE = B3500000; break;
    case 4000000 : BAUDRATE = B4000000; break;
    default      : return false;
  }
  return true;
}