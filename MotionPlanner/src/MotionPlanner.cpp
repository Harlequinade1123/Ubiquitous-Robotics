// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  MotionPlanner.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "MotionPlanner.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const motionplanner_spec[] =
#else
static const char* motionplanner_spec[] =
#endif
  {
    "implementation_id", "MotionPlanner",
    "type_name",         "MotionPlanner",
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
MotionPlanner::MotionPlanner(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandIn("command", m_command),
    m_dynamixel_poseOut("dynamixel_pose", m_dynamixel_pose),
    m_wheel_velocityOut("wheel_velocity", m_wheel_velocity),
    m_motion_stateOut("motion_state", m_motion_state)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MotionPlanner::~MotionPlanner()
{
}



RTC::ReturnCode_t MotionPlanner::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("command", m_commandIn);
  
  // Set OutPort buffer
  addOutPort("dynamixel_pose", m_dynamixel_poseOut);
  addOutPort("wheel_velocity", m_wheel_velocityOut);
  addOutPort("motion_state", m_motion_stateOut);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotionPlanner::onActivated(RTC::UniqueId /*ec_id*/)
{
  GRIPPER_CLOSE_ANGLE =  M_PI * 20 / 180;
  GRIPPER_OPEN_ANGLE  = -M_PI * 30 / 180;
  GRIPPER_NORMAL_ANGLE = 0;
  BASE_NORMAL_ANGLE    = -M_PI_2;
  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE, 10);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotionPlanner::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotionPlanner::onExecute(RTC::UniqueId /*ec_id*/)
{
  if (m_commandIn.isNew())
  {
    m_commandIn.read();
    received_command = m_command.data;
    printf("GET %d\n", m_command.data);

    if (100 <= received_command)
    {
      sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE);
      if (100 == received_command)
      {
        sendRobotCommand(0, 0, 0);
      }
      else if (101 == received_command)
      {
        sendRobotCommand(0.3, 0, 0);
      }
      else if (102 == received_command)
      {
        sendRobotCommand(-0.3, 0, 0);
      }
      else if (103 == received_command)
      {
        sendRobotCommand(0, 0.3, 0);
      }
      else if (104 == received_command)
      {
        sendRobotCommand(0, -0.3, 0);
      }
      else if (105 == received_command)
      {
        sendRobotCommand(0, 0, M_PI_2);
      }
      else if (106 == received_command)
      {
        sendRobotCommand(0, 0, -M_PI_2);
      }
      else if (107 == received_command)
      {
        sendFetchCommand();
      }
      else if (108 == received_command)
      {
        sendReturnCommand();
      }
      usleep(50000);
      return RTC::RTC_OK;
    }
    
    // ツールの場所まで移動
    if (received_command % 10 == 1)
    {
      sendRobotCommand(0.2, 0, 0, 6000);
      sendRobotCommand(0, 0.2, 0, 3000);
    }
    else if (received_command % 10 == 2)
    {
      sendRobotCommand(0.2, 0, 0, 6000);
      sendRobotCommand(0, -0.2, 0, 3000);
    }
    
    // ツールを受け取る or 返す (20000 ms)
    if (received_command < 10)
    {
      // ツールを受け取る
      sendFetchCommand();
    }
    else
    {
      // ツールを返す
      sendReturnCommand();
    }

    // 元の場所まで移動
    if (received_command % 10 == 1)
    {
      sendRobotCommand(0, -0.2, 0, 3000);
      sendRobotCommand(-0.2, 0, 0, 6000);
    }
    else if (received_command % 10 == 2)
    {
      sendRobotCommand(0, 0.2, 0, 3000);
      sendRobotCommand(-0.2, 0, 0, 6000);
    }
  }
  return RTC::RTC_OK;
}

void MotionPlanner::sendRobotCommand(double x_vel, double y_vel, double anguler_vel, int time_count_ms)
{
  m_wheel_velocity.data.vx = x_vel;
  m_wheel_velocity.data.vy = y_vel;
  m_wheel_velocity.data.va = anguler_vel;
  setTimestamp(m_wheel_velocity);
  m_wheel_velocityOut.write();
  usleep(time_count_ms * 1000);
  m_wheel_velocity.data.vx = 0;
  m_wheel_velocity.data.vy = 0;
  m_wheel_velocity.data.va = 0;
  setTimestamp(m_wheel_velocity);
  m_wheel_velocityOut.write();
}

void MotionPlanner::sendRobotCommand(double x_vel, double y_vel, double anguler_vel)
{
  m_wheel_velocity.data.vx = x_vel;
  m_wheel_velocity.data.vy = y_vel;
  m_wheel_velocity.data.va = anguler_vel;
  setTimestamp(m_wheel_velocity);
  m_wheel_velocityOut.write();
}

void MotionPlanner::sendArmCommand(double base_angle, double x, double z, double posture, double gripper, int time_count_ms)
{
  m_dynamixel_pose.data.length(5);
  m_dynamixel_pose.data[0] = base_angle;
  m_dynamixel_pose.data[1] = x;
  m_dynamixel_pose.data[2] = z;
  m_dynamixel_pose.data[3] = posture;
  m_dynamixel_pose.data[4] = gripper;
  setTimestamp(m_dynamixel_pose);
  m_dynamixel_poseOut.write();
  usleep(time_count_ms * 1000);
}

void MotionPlanner::sendArmCommand(double base_angle, double x, double z, double posture, double gripper)
{
  m_dynamixel_pose.data.length(5);
  m_dynamixel_pose.data[0] = base_angle;
  m_dynamixel_pose.data[1] = x;
  m_dynamixel_pose.data[2] = z;
  m_dynamixel_pose.data[3] = posture;
  m_dynamixel_pose.data[4] = gripper;
  setTimestamp(m_dynamixel_pose);
  m_dynamixel_poseOut.write();
}

void MotionPlanner::sendFetchCommand()
{
  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 500);
  // ツールを掴む
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE, 145 + i * 2, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE, 145 + 100, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 1000);

  // 台車に乗せる
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE, 145 + 100 - i * 2, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  for (int i = 1; i <= 20; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI / 20 * i, 145, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 145 + i * 2, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 175 - i * 2, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 75, -M_PI_2, GRIPPER_OPEN_ANGLE, 1000);

  // アームを元の位置に戻す
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 75 + i * 2, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245 - i * 2, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE, 50);
  }
  for (int i = 1; i <= 20; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI - M_PI / 20 * i, 145, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE, 500);
}

void MotionPlanner::sendReturnCommand()
{
  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 500);
  // アームで台車に乗っているツールを掴む
  for (int i = 1; i <= 20; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI / 20 * i, 145, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 145 + i * 2, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 175 - i * 2, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 75, -M_PI_2, GRIPPER_CLOSE_ANGLE, 1000);

  // ツールを掴んだままアームを元の位置に戻す
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245, 75 + i * 2, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI, 245 - i * 2, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  for (int i = 1; i <= 20; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE + M_PI - M_PI / 20 * i, 145, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }

  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 1000);

  // ツールを置く
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE, 145 + i * 2, 175, -M_PI_2, GRIPPER_CLOSE_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE, 145 + 100, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 1000);

  // アームを元の位置に戻す
  for (int i = 1; i <= 50; i++)
  {
    sendArmCommand(BASE_NORMAL_ANGLE, 145 + 100 - i * 2, 175, -M_PI_2, GRIPPER_OPEN_ANGLE, 50);
  }
  sendArmCommand(BASE_NORMAL_ANGLE, 145, 175, -M_PI_2, GRIPPER_NORMAL_ANGLE, 500);
}


extern "C"
{
 
  void MotionPlannerInit(RTC::Manager* manager)
  {
    coil::Properties profile(motionplanner_spec);
    manager->registerFactory(profile,
                             RTC::Create<MotionPlanner>,
                             RTC::Delete<MotionPlanner>);
  }
  
}
