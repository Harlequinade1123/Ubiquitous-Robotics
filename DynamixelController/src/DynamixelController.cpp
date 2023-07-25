// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  DynamixelController.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "DynamixelController.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const dynamixelcontroller_spec[] =
#else
static const char* dynamixelcontroller_spec[] =
#endif
  {
    "implementation_id", "DynamixelController",
    "type_name",         "DynamixelController",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DynamixelController::DynamixelController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandIn("command", m_command),
    m_poseIn("pose", m_pose)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DynamixelController::~DynamixelController()
{
}



RTC::ReturnCode_t DynamixelController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("command", m_commandIn);
  addInPort("pose", m_poseIn);
  
  // Set OutPort buffer

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  
  return RTC::RTC_OK;
}



RTC::ReturnCode_t DynamixelController::onActivated(RTC::UniqueId /*ec_id*/)
{
  char device_name[]="/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_AG0K5ARF-if00-port0";
  port.openSerial(device_name, 57600);

  double links[4]  = {77, 85, 95, 140};
  arm = FourAxisArm(links);

  usleep(500000);
  port.writeCommand("[n]\n");
  port.writeCommand("[v,160]\n");
  //port.writeCommand("[i]\n");
  usleep(500000);
  port.writeCommand("[e]\n");
  usleep(500000);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DynamixelController::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  port.closeSerial();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DynamixelController::onExecute(RTC::UniqueId /*ec_id*/)
{
  /**
  if (m_commandIn.isNew())
  {
    m_commandIn.read();
    if (m_command.data == 1)
    {
      port.writeCommand("[i]\n");
    }
    else if (m_command.data == 2)
    {
      port.writeCommand("[m,1,512,2,512,3,256,4,256,5,512]\n");
    }
    else if (m_command.data == 3)
    {
      port.writeCommand("[m,1,512,2,512,3,256,4,512,5,512]\n");
    }
  }
  **/
  if (m_poseIn.isNew())
  {
    m_poseIn.read();
    std::cout << "GET" << std::endl;

    int base_val    = arm.mapFunc(m_pose.data[0], -M_PI * 5.0 / 6.0, M_PI * 5.0 / 6.0, 0, 1024);
    int gripper_val = arm.mapFunc(m_pose.data[4], -M_PI * 5.0 / 6.0, M_PI * 5.0 / 6.0, 0, 1024);
    
    double pose[3];
    int    vals[3];
    std::cout << m_pose.data[0] << " " << m_pose.data[4] << std::endl;
    std::cout << m_pose.data[1] << " " << m_pose.data[2] << " " << m_pose.data[3] << std::endl;
    pose[0] = m_pose.data[1];
    pose[1] = m_pose.data[2];
    pose[2] = m_pose.data[3];

    arm.calcInverse(pose);
    arm.getMotorValues(vals);

    int command_vals[5];
    command_vals[0] = base_val;
    command_vals[1] = vals[0];
    command_vals[2] = vals[1];
    command_vals[3] = vals[2];
    command_vals[4] = gripper_val;

    std::string command = "[m";
    for (int val_i = 0; val_i < 5; val_i++)
    {
      command += ",";
      command += std::to_string(val_i + 1);
      command += ",";
      command += std::to_string(command_vals[val_i]);
    }
    command += "]\n";
    
    port.writeCommand(command);
  }
  return RTC::RTC_OK;
}

extern "C"
{
 
  void DynamixelControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(dynamixelcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<DynamixelController>,
                             RTC::Delete<DynamixelController>);
  }
  
}