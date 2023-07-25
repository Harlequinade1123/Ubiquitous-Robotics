// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  DynamixelControllerTest.cpp
 * @brief ModuleDescription (test code)
 *
 */
// </rtc-template>

#include "DynamixelControllerTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const dynamixelcontroller_spec[] =
#else
static const char* dynamixelcontroller_spec[] =
#endif
  {
    "implementation_id", "DynamixelControllerTest",
    "type_name",         "DynamixelControllerTest",
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
DynamixelControllerTest::DynamixelControllerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandOut("command", m_command),
    m_coordinateOut("coordinate", m_coordinate)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DynamixelControllerTest::~DynamixelControllerTest()
{
}



RTC::ReturnCode_t DynamixelControllerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("command", m_commandOut);
  addOutPort("coordinate", m_coordinateOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DynamixelControllerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t DynamixelControllerTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t DynamixelControllerTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t DynamixelControllerTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DynamixelControllerTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DynamixelControllerTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t DynamixelControllerTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t DynamixelControllerTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t DynamixelControllerTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t DynamixelControllerTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t DynamixelControllerTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool DynamixelControllerTest::runTest()
{
    return true;
}


extern "C"
{
 
  void DynamixelControllerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(dynamixelcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<DynamixelControllerTest>,
                             RTC::Delete<DynamixelControllerTest>);
  }
  
}
