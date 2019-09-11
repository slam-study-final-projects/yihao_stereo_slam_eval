#include "slam_work.h"

int main(int argc, char** argv) {
	SlamWork slam_work;
	slam_work.SetParams(718.856, 718.856, 607.1928, 185.2157, 0.386);// Input manually.
	std::string in_path = *(argv+1);
	slam_work.input_path_ = in_path;
	slam_work.pose_number_ = 5; // Test < 5 images;
	slam_work.R_world_ << 1,0,0,0,1,0,0,0,1;
	slam_work.t_world_ << 0,0,0;
	slam_work.ComputePose();
	return 0;
}
