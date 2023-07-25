// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  testVelocity2D.cpp
 * @brief Test TimedVelocity2D OutPort Component
 *
 * LGPL
 *
 */
// </rtc-template>

#include "testVelocity2D.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const testvelocity2d_spec[] =
#else
static const char* testvelocity2d_spec[] =
#endif
  {
    "implementation_id", "testVelocity2D",
    "type_name",         "testVelocity2D",
    "description",       "Test TimedVelocity2D OutPort Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.speed_x", "0.0",
    "conf.default.speed_y", "0.0",
    "conf.default.speed_r", "0.0",

    // Widget
    "conf.__widget__.speed_x", "slider.0.1",
    "conf.__widget__.speed_y", "slider.0.1",
    "conf.__widget__.speed_r", "slider.0.1",
    // Constraints
    "conf.__constraints__.speed_x", "-10.0<x<10.0",
    "conf.__constraints__.speed_y", "-10.0<x<10.0",
    "conf.__constraints__.speed_r", "-3.0<x<3.0",

    "conf.__type__.speed_x", "double",
    "conf.__type__.speed_y", "double",
    "conf.__type__.speed_r", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
testVelocity2D::testVelocity2D(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out),
    m_inIn("in", m_in)
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
testVelocity2D::~testVelocity2D()
{
}



RTC::ReturnCode_t testVelocity2D::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  addInPort("in", m_inIn);

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("speed_x", m_speed_x, "0.0");
  bindParameter("speed_y", m_speed_y, "0.0");
  bindParameter("speed_r", m_speed_r, "0.0");
  // </rtc-template>

  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t testVelocity2D::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t testVelocity2D::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t testVelocity2D::onExecute(RTC::UniqueId /*ec_id*/)
{
  if (m_inIn.isNew())
  {
    m_inIn.read();
    std::cout << "GET " << m_in.data.vx << " " << m_in.data.vy << " " << m_in.data.va << std::endl;
    m_out.data.vx = m_in.data.vx;
    m_out.data.vy = m_in.data.vy;
    m_out.data.va = m_in.data.va;
    setTimestamp(m_out);
    m_outOut.write();
  }
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t testVelocity2D::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t testVelocity2D::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}



extern "C"
{
 
  void testVelocity2DInit(RTC::Manager* manager)
  {
    coil::Properties profile(testvelocity2d_spec);
    manager->registerFactory(profile,
                             RTC::Create<testVelocity2D>,
                             RTC::Delete<testVelocity2D>);
  }
  
}
