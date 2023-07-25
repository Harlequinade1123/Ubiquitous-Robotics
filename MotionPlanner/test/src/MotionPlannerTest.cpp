// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  MotionPlannerTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "MotionPlannerTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const motionplanner_spec[] =
#else
static const char* motionplanner_spec[] =
#endif
  {
    "implementation_id", "MotionPlannerTest",
    "type_name",         "MotionPlannerTest",
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
MotionPlannerTest::MotionPlannerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandOut("command", m_command),
    m_dynamixel_positionIn("dynamixel_position", m_dynamixel_position),
    m_wheel_velocityIn("wheel_velocity", m_wheel_velocity),
    m_motion_stateIn("motion_state", m_motion_state)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MotionPlannerTest::~MotionPlannerTest()
{
}



RTC::ReturnCode_t MotionPlannerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("dynamixel_position", m_dynamixel_positionIn);
  addInPort("wheel_velocity", m_wheel_velocityIn);
  addInPort("motion_state", m_motion_stateIn);
  
  // Set OutPort buffer
  addOutPort("command", m_commandOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MotionPlannerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t MotionPlannerTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t MotionPlannerTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t MotionPlannerTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotionPlannerTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MotionPlannerTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t MotionPlannerTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t MotionPlannerTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t MotionPlannerTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t MotionPlannerTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t MotionPlannerTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool MotionPlannerTest::runTest()
{
    return true;
}


extern "C"
{
 
  void MotionPlannerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(motionplanner_spec);
    manager->registerFactory(profile,
                             RTC::Create<MotionPlannerTest>,
                             RTC::Delete<MotionPlannerTest>);
  }
  
}
