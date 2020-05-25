// Generated by gencpp from file franka_control/SetFullCollisionBehaviorResponse.msg
// DO NOT EDIT!


#ifndef FRANKA_CONTROL_MESSAGE_SETFULLCOLLISIONBEHAVIORRESPONSE_H
#define FRANKA_CONTROL_MESSAGE_SETFULLCOLLISIONBEHAVIORRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace franka_control
{
template <class ContainerAllocator>
struct SetFullCollisionBehaviorResponse_
{
  typedef SetFullCollisionBehaviorResponse_<ContainerAllocator> Type;

  SetFullCollisionBehaviorResponse_()
    : success(false)
    , error()  {
    }
  SetFullCollisionBehaviorResponse_(const ContainerAllocator& _alloc)
    : success(false)
    , error(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _error_type;
  _error_type error;





  typedef boost::shared_ptr< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetFullCollisionBehaviorResponse_

typedef ::franka_control::SetFullCollisionBehaviorResponse_<std::allocator<void> > SetFullCollisionBehaviorResponse;

typedef boost::shared_ptr< ::franka_control::SetFullCollisionBehaviorResponse > SetFullCollisionBehaviorResponsePtr;
typedef boost::shared_ptr< ::franka_control::SetFullCollisionBehaviorResponse const> SetFullCollisionBehaviorResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace franka_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'franka_control': ['/home/rnm/rnm_group_2/devel/share/franka_control/msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "45872d25d65c97743cc71afc6d4e884d";
  }

  static const char* value(const ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x45872d25d65c9774ULL;
  static const uint64_t static_value2 = 0x3cc71afc6d4e884dULL;
};

template<class ContainerAllocator>
struct DataType< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "franka_control/SetFullCollisionBehaviorResponse";
  }

  static const char* value(const ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n"
"string error\n"
"\n"
"\n"
;
  }

  static const char* value(const ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
      stream.next(m.error);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetFullCollisionBehaviorResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::franka_control::SetFullCollisionBehaviorResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "error: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.error);
  }
};

} // namespace message_operations
} // namespace ros

#endif // FRANKA_CONTROL_MESSAGE_SETFULLCOLLISIONBEHAVIORRESPONSE_H
