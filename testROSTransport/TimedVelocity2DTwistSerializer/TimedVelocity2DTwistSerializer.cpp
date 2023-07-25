#include <rtm/ByteDataStreamBase.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <coil/Factory.h>
#include <rtm/Manager.h>
#include <rtm/ext/ROSTransport/ROSSerializer.h>
#include <geometry_msgs/Twist.h>

//以下はシリアライザの実装
class TimedVelocity2DTwistSerializer : public RTC::ROSSerializerBase<RTC::TimedVelocity2D>
{
public:
    TimedVelocity2DTwistSerializer(){};

    
 
    bool serialize(const RTC::TimedVelocity2D& data) override
    {
        geometry_msgs::Twist msg;
        msg.linear.x = data.data.vx;
        msg.linear.y = data.data.vy;
        msg.angular.z = data.data.va;

        RTC::ROSSerializerBase<RTC::TimedVelocity2D>::m_message = ros::serialization::serializeMessage<geometry_msgs::Twist>(msg);
        return true;
    }
    bool deserialize(RTC::TimedVelocity2D& data) override
    {
        geometry_msgs::Twist msg;
        ros::serialization::deserializeMessage(ROSSerializerBase<RTC::TimedVelocity2D>::m_message, msg);
        data.data.vx = msg.linear.x;
        data.data.vy = msg.linear.y;
        data.data.va = msg.angular.z;

        return true;
    }
private:

};

extern "C"
{
    //以下はモジュールロード時に呼び出される関数
    DLL_EXPORT void TimedVelocity2DTwistSerializerInit(RTC::Manager* /*manager*/)
    {
        //シリアライザの登録
        RTC::addRosSerializer<RTC::TimedVelocity2D, geometry_msgs::Twist, TimedVelocity2DTwistSerializer>("ros:geometry_msgs/Twist");
    }
}
