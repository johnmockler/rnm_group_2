// Generated by gencpp from file franka_gripper/GraspActionGoal.msg
// DO NOT EDIT!


#ifndef FRANKA_GRIPPER_MESSAGE_GRASPACTIONGOAL_H
#define FRANKA_GRIPPER_MESSAGE_GRASPACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <franka_gripper/GraspGoal.h>

namespace franka_gripper
{
template <class ContainerAllocator>
struct GraspActionGoal_
{
  typedef GraspActionGoal_<ContainerAllocator> Type;

  GraspActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  GraspActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::franka_gripper::GraspGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::franka_gripper::GraspActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::franka_gripper::GraspActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct GraspActionGoal_

typedef ::franka_gripper::GraspActionGoal_<std::allocator<void> > GraspActionGoal;

typedef boost::shared_ptr< ::franka_gripper::GraspActionGoal > GraspActionGoalPtr;
typedef boost::shared_ptr< ::franka_gripper::GraspActionGoal const> GraspActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::franka_gripper::GraspActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace franka_gripper

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'franka_gripper': ['/home/rnm/rnm_group_2/devel/share/franka_gripper/msg', '/home/rnm/rnm_group_2/src/franka_ros/franka_gripper/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::franka_gripper::GraspActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::franka_gripper::GraspActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::franka_gripper::GraspActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7bd1a6e7f94ef15bb6dd05cb170e7909";
  }

  static const char* value(const ::franka_gripper::GraspActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7bd1a6e7f94ef15bULL;
  static const uint64_t static_value2 = 0xb6dd05cb170e7909ULL;
};

template<class ContainerAllocator>
struct DataType< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "franka_gripper/GraspActionGoal";
  }

  static const char* value(const ::franka_gripper::GraspActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalID goal_id\n"
"GraspGoal goal\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalID\n"
"# The stamp should store the time at which this goal was requested.\n"
"# It is used by an action server when it tries to preempt all\n"
"# goals that were requested before a certain time\n"
"time stamp\n"
"\n"
"# The id provides a way to associate feedback and\n"
"# result message with specific goal requests. The id\n"
"# specified must be unique.\n"
"string id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: franka_gripper/GraspGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"float64 width # [m]\n"
"GraspEpsilon epsilon\n"
"float64 speed # [m/s]\n"
"float64 force # [N]\n"
"\n"
"================================================================================\n"
"MSG: franka_gripper/GraspEpsilon\n"
"float64 inner # [m]\n"
"float64 outer # [m]\n"
;
  }

  static const char* value(const ::franka_gripper::GraspActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GraspActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::franka_gripper::GraspActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::franka_gripper::GraspActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::franka_gripper::GraspGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // FRANKA_GRIPPER_MESSAGE_GRASPACTIONGOAL_H
