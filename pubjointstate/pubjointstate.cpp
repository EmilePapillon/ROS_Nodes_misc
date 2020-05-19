#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Header.h>
#include <std_msgs/String.h>
#include <stdlib.h>
#include <vector>



class PositionPublisher {
public:
	PositionPublisher()
	{
	pub_ = n_.advertise<sensor_msgs::JointState>(
		"desired_position", 1000);

	sub_ = n_.subscribe("aChatter", 1000, &PositionPublisher::acceleration_data_callback, this); 
	}

	void acceleration_data_callback(const std_msgs::String &msg)
	{
		//ROS_INFO_STREAM("calling call back");

		std::vector<float> parsed; 
		std::stringstream s_stream(msg.data);

	 	while(s_stream.good()) 
	 	{
		 	std::string substr;
	        getline(s_stream, substr, ','); //get first string delimited by comma
	        parsed.push_back(std::stof(substr));
        }


        ROS_DEBUG_STREAM("Received data:");
	    for(int i = 0 ; i < parsed.size() ; i++)
	    {
	    	ROS_DEBUG_STREAM(parsed[i]); 
	    }

	    if ( parsed.size() >= 3)
	    {

			sensor_msgs::JointState pub_msg; 
			pub_msg.header = std_msgs::Header();
			pub_msg.name.push_back("cellphone_pitch");
			pub_msg.name.push_back("cellphone_yaw");
			pub_msg.name.push_back("cellphone_roll");
			pub_msg.position.push_back(parsed[1]);
			pub_msg.position.push_back(-parsed[0]);
			pub_msg.position.push_back(parsed[2]);
			//pub_msg.velocity = {};
			//pub_msg.effort = {}; 

			pub_.publish(pub_msg);
		}
	
	}

private:
	ros::NodeHandle n_;
	ros::Publisher pub_;
	ros::Subscriber sub_;

};


int main(int argc, char **argv)
{

	//Creating publisher object
	ros::init(argc, argv, "publish_joint_state");
	ros::NodeHandle nh; 

	PositionPublisher PPObject;

	ros::spin(); 

	return 0; 

}
