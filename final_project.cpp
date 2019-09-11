#include "slam_work.h"

int main(int argc, char** argv) {
	std::cout << "Please input like this: /path/to/kitti/sequence/ fx fy cx cy baseline number_of_frames"<< std::endl;
	SlamWork slam_work;
	std::string fx(*(argv+2)),fy(*(argv+3)),cx(*(argv+4)),cy(*(argv+5)),baseline(*(argv+6));
	std::cout << "fx = " << std::stof(fx) << std::endl;
	std::cout << "fy = " << std::stof(fy) << std::endl;
	std::cout << "cx = " << std::stof(cx) << std::endl;
	std::cout << "cy = " << std::stof(cy) << std::endl;
	std::cout << "stereo baseline = " << std::stof(baseline) << std::endl;
	slam_work.SetParams(std::stof(fx), std::stof(fy), std::stof(cx), std::stof(cy),std::stof(baseline));// 718.856, 718.856, 607.1928, 185.2157, 0.537166 // Input manually.
	std::string in_path = *(argv+1);
	slam_work.input_path_ = in_path;
	std::cout << "kitti dir = " << slam_work.input_path_ << std::endl;
	std::string num_frames(*(argv+7));
	slam_work.pose_number_ = std::stoi(num_frames);
	std::cout << "number of frames = " << slam_work.pose_number_  << std::endl;
	slam_work.R_world_ << 1,0,0,0,1,0,0,0,1;
	slam_work.t_world_ << 0,0,0;
	slam_work.ComputePose();
	return 0;
}
