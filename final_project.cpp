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
//
//using namespace std;
//using namespace Eigen;
//
//typedef vector<Vector3d, Eigen::aligned_allocator<Vector3d>> VecVector3d;
//typedef vector<Vector2d, Eigen::aligned_allocator<Vector3d>> VecVector2d;
//typedef Matrix<double, 6, 1> Vector6d;
//
//const double pi = 3.1415926; //
//
//// 文件路径，如果不对，请调整
//string first_left_file = "./left_000000.png";
//string first_right_file = "./right_000000.png";
//string first_disparity_ref_file = "./disparity.png";
//string second_left_file = "./left_000001.png";
//string second_right_file = "./right_000001.png";
//
//// BilinearInterpolation for accurate depth of feature point.
//float findDepth(const cv::Mat &depth_image, const cv::Point2f &point);
//
//// ORB descriptor functions
//void computeAngle(const cv::Mat &image, vector<cv::KeyPoint> &keypoints);
//
//typedef vector<bool> DescType; // type of descriptor, 256 bools
//void computeORBDesc(const cv::Mat &image, vector<cv::KeyPoint> &keypoints,
//                    vector<DescType> &desc);
//
//// 在panglin中画图，已写好，无需调整
//void showPointCloud(
//    const vector<Vector4d, Eigen::aligned_allocator<Vector4d>> &pointcloud);
//
//void bfMatch(const vector<DescType> &desc1, const vector<DescType> &desc2,
//             vector<cv::DMatch> &matches);
//
///*******************************************************************************************/
//bool DrawTrace(const vector<Eigen::Vector3d> &pi_g,
//               const vector<Eigen::Vector3d> &pi_e, const string &name);
//
//int main(int argc, char **argv) {
//
//  // 内参
//  double fx = 718.856, fy = 718.856, cx = 607.1928, cy = 185.2157;
//  // 间距
//  double d = 0.386; // 0.386; // 0.573 ?
//
//  // Compute first image depth.
//
//  // 读取图像
//  cv::Mat left = cv::imread(first_left_file, 0);
//  cv::Mat right = cv::imread(first_right_file, 0);
//  cv::Mat disparity; // = cv::imread(disparity_file, 0); // disparty
//                     // 为CV_8U,单位为像素
//  cv::Mat disparity_ref =
//      cv::imread(first_disparity_ref_file, 0); // disparty 为CV_8U,单位为像素
//  cv::Mat disparity_diff = disparity_ref - disparity;
//  cv::Mat depth_image(left.rows, left.cols, CV_32FC1);
//
//  int mindisparity = 0;
//  int ndisparities = 96;  // 64;
//  int SADWindowSize = 11; // 11;
//
//  // SGBM
//  cv::Ptr<cv::StereoSGBM> sgbm =
//      cv::StereoSGBM::create(mindisparity, ndisparities, SADWindowSize);
//  int P1 = 8 * left.channels() * SADWindowSize * SADWindowSize;
//  int P2 = 32 * left.channels() * SADWindowSize * SADWindowSize;
//  sgbm->setP1(P1);
//  sgbm->setP2(P2);
//  sgbm->setPreFilterCap(15);
//  sgbm->setUniquenessRatio(10);
//  sgbm->setSpeckleRange(2);
//  sgbm->setSpeckleWindowSize(100);
//  sgbm->setDisp12MaxDiff(1);
//  // sgbm->setMode(cv::StereoSGBM::MODE_HH);
//  sgbm->compute(left, right, disparity);
//  disparity.convertTo(disparity, CV_32F, 1.0 / 16);
//
//  // 生成点云
//  vector<Vector4d, Eigen::aligned_allocator<Vector4d>> pointcloud;
//
//  // TODO 根据双目模型计算点云 - Finished
//  // 如果你的机器慢，请把后面的v++和u++改成v+=2, u+=2
//  for (int v = 0; v < left.rows; v++)
//    for (int u = 0; u < left.cols; u++) {
//
//      Vector4d point(0, 0, 0,
//                     left.at<uchar>(v, u) / 255.0); // 前三维为xyz,第四维为颜色
//
//      // start your code here (~6 lines)
//      // 根据双目模型计算 point 的位置
//      double z = d / (disparity.at<float>(v, u) /
//                      fx);   // 先计算z的值 // switch uchar to float
//      if (z > 0 && z < 15) { // 判断z是否有效，可提升计算效率
//        point[2] = z;
//        point[0] = (static_cast<double>(u) - cx) / fx * z; // 通过z计算x和y
//        point[1] = (static_cast<double>(v) - cy) / fy * z;
//        pointcloud.emplace_back(point);
//        depth_image.at<float>(v, u) = z; // meter as unit.
//      } else {
//        depth_image.at<float>(v, u) = 0;
//      }
//      continue;
//      // end your code here
//    }
//
//  // 画出点云
//  // showPointCloud(pointcloud);
//
//  // Compute second image depth.
//  // 读取图像
//  cv::Mat left2 = cv::imread(second_left_file, 0);
//  cv::Mat right2 = cv::imread(second_right_file, 0);
//  cv::Mat disparity2; // = cv::imread(disparity_file, 0); // disparty
//                      // 为CV_8U,单位为像素
//  // cv::Mat disparity_ref = cv::imread(first_disparity_ref_file, 0); //
//  // disparty 为CV_8U,单位为像素 cv::Mat disparity_diff = disparity_ref -
//  // disparity;
//  cv::Mat depth_image2(left2.rows, left2.cols, CV_32FC1);
//
//  // int mindisparity = 0;
//  // int ndisparities = 96;// 64;
//  // int SADWindowSize = 11;// 11;
//
//  // SGBM
//  cv::Ptr<cv::StereoSGBM> sgbm2 =
//      cv::StereoSGBM::create(mindisparity, ndisparities, SADWindowSize);
//  // int P1 = 8 * left.channels() * SADWindowSize* SADWindowSize;
//  // int P2 = 32 * left.channels() * SADWindowSize* SADWindowSize;
//  sgbm2->setP1(P1);
//  sgbm2->setP2(P2);
//  sgbm2->setPreFilterCap(15);
//  sgbm2->setUniquenessRatio(10);
//  sgbm2->setSpeckleRange(2);
//  sgbm2->setSpeckleWindowSize(100);
//  sgbm2->setDisp12MaxDiff(1);
//  // sgbm->setMode(cv::StereoSGBM::MODE_HH);
//  sgbm2->compute(left2, right2, disparity2);
//  disparity2.convertTo(disparity2, CV_32F, 1.0 / 16);
//
//  // 生成点云
//  vector<Vector4d, Eigen::aligned_allocator<Vector4d>> pointcloud2;
//
//  // TODO 根据双目模型计算点云 - Finished
//  // 如果你的机器慢，请把后面的v++和u++改成v+=2, u+=2
//  for (int v = 0; v < left2.rows; v++)
//    for (int u = 0; u < left2.cols; u++) {
//
//      Vector4d point2(
//          0, 0, 0, left2.at<uchar>(v, u) / 255.0); // 前三维为xyz,第四维为颜色
//
//      // start your code here (~6 lines)
//      // 根据双目模型计算 point 的位置
//      double z = d / (disparity2.at<float>(v, u) /
//                      fx);   // 先计算z的值 // switch uchar to float
//      if (z > 0 && z < 15) { // 判断z是否有效，可提升计算效率
//        point2[2] = z;
//        point2[0] = (static_cast<double>(u) - cx) / fx * z; // 通过z计算x和y
//        point2[1] = (static_cast<double>(v) - cy) / fy * z;
//        pointcloud.emplace_back(point2);
//        depth_image2.at<float>(v, u) = z; // meter as unit.
//      } else {
//        depth_image2.at<float>(v, u) = 0;
//      }
//      continue;
//      // end your code here
//    }
//
//  // ORB matching
//  // load image
//  cv::Mat first_image = cv::imread(first_left_file, 0); // load grayscale image
//  cv::Mat second_image =
//      cv::imread(second_left_file, 0); // load grayscale image
//
//  // plot the image
//  // cv::imshow("first image", first_image);
//  // cv::imshow("second image", second_image);
//  // cv::waitKey(0);
//
//  // detect FAST keypoints using threshold=40
//  vector<cv::KeyPoint> keypoints;
//  cv::FAST(first_image, keypoints, 40);
//  cout << "keypoints: " << keypoints.size() << endl;
//
//  vector<cv::Point3f> depth_points(0);
//  vector<cv::Point2f> image_points(0);
//
//  for (auto i = 0; i < keypoints.size(); ++i) {
//    float z = findDepth(depth_image, keypoints[i].pt);
//    if (z <= 0) {
//      keypoints.erase(keypoints.begin() + i);
//      i--;
//    } else {
//
//      depth_points.emplace_back(
//          (static_cast<double>(keypoints[i].pt.x) - cx) / fx * z,
//          (static_cast<double>(keypoints[i].pt.y) - cy) / fy * z, z);
//      image_points.emplace_back(keypoints[i].pt.x, keypoints[i].pt.y);
//    }
//  }
//
//  // compute angle for each keypoint
//  computeAngle(first_image, keypoints);
//
//  // compute ORB descriptors
//  vector<DescType> descriptors;
//  computeORBDesc(first_image, keypoints, descriptors);
//
//  // plot the keypoints
//  cv::Mat image_show;
//  cv::drawKeypoints(first_image, keypoints, image_show, cv::Scalar::all(-1),
//                    cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//  // cv::imshow("features", image_show);
//  cv::imwrite("feat1.png", image_show);
//  // cv::waitKey(0);
//
//  // we can also match descriptors between images
//  // same for the second
//  vector<cv::KeyPoint> keypoints2;
//  cv::FAST(second_image, keypoints2, 40);
//  cout << "keypoints2: " << keypoints2.size() << endl;
//
//  vector<cv::Point3f> depth_points2(0);
//  vector<cv::Point2f> image_points2(0);
//
//  for (auto i = 0; i < keypoints2.size(); ++i) {
//    float z = findDepth(depth_image2, keypoints2[i].pt);
//    if (z <= 0) {
//      keypoints2.erase(keypoints2.begin() + i);
//      i--;
//    } else {
//
//      depth_points2.emplace_back(
//          (static_cast<double>(keypoints2[i].pt.x) - cx) / fx * z,
//          (static_cast<double>(keypoints2[i].pt.y) - cy) / fy * z, z);
//      image_points2.emplace_back(keypoints2[i].pt.x, keypoints2[i].pt.y);
//    }
//  }
//
//  // std::cout << "image_points : " << image_points.size() << "  image_points2 :
//  // "<< image_points2.size() << std::endl;
//
//  // compute angle for each keypoint
//  computeAngle(second_image, keypoints2);
//
//  // compute ORB descriptors
//  vector<DescType> descriptors2;
//  computeORBDesc(second_image, keypoints2, descriptors2);
//
//  // find matches
//  vector<cv::DMatch> matches;
//  bfMatch(descriptors, descriptors2, matches);
//  cout << "matches: " << matches.size() << endl;
//
//  // plot the matches
//  cv::drawMatches(first_image, keypoints, second_image, keypoints2, matches,
//                  image_show);
//  // cv::imshow("matches", image_show);
//  // cv::imwrite("matches.png", image_show);
//  // cv::waitKey(0);
//
//  cout << "done(matching)." << endl;
//
//  //  // We can use either 3D-3D(ICP) or 3D-2D(Projection) method. Here I choose
//  //  3D-
//  //  // 2D GN-BA for the pose computing.
//  //  VecVector2d p2d;
//  //  VecVector3d p3d;
//  //  Matrix3d K;
//  //
//  //  // Camera matrix.
//  //  K << fx, 0, cx, 0, fy, cy, 0, 0, 1;
//  //
//  //  // load points in to p3d and p2d
//  //  // START YOUR CODE HERE
//  //
//  //  for (int k = 0; k < matches.size(); ++k) {
//  //  	p3d.emplace_back(depth_points[matches[k].queryIdx].x,
//  //  depth_points[matches[k].queryIdx].y, depth_points[matches[k].queryIdx].z);
//  //  	p2d.emplace_back(image_points2[matches[k].trainIdx].x,
//  //  image_points2[matches[k].trainIdx].y);
//  //  }
//  //
//  //  // END YOUR CODE HERE
//  //  assert(p3d.size() == p2d.size());
//  //
//  //  int iterations = 100;
//  //  double cost = 0, lastCost = 0;
//  //  int nPoints = p3d.size();
//  //  cout << "points: " << nPoints << endl;
//  //
//  //  Sophus::SE3 T_esti; // estimated pose, 初始估计 T = I
//  //
//  //  for (int iter = 0; iter < iterations; iter++) {
//  //
//  //    Matrix<double, 6, 6> H = Matrix<double, 6, 6>::Zero();
//  //    Vector6d b = Vector6d::Zero();
//  //
//  //    cost = 0;
//  //    // compute cost
//  //    for (int i = 0; i < nPoints; i++) {
//  //      // compute cost for p3d[I] and p2d[I]
//  //      // START YOUR CODE HERE
//  //      Vector3d p_prime =
//  //          T_esti *
//  //          p3d[i]; // 计算p'，不能使用SE3.matrix()相乘，直接乘就好，结果正确
//  //      // cout << "p_prime = " << p_prime << endl;
//  //
//  //      // 验证:
//  //      //
//  //      以下使用SE3.matrix()与齐次坐标相乘的方式，结果同上方简便相乘结果一致
//  //      // Vector4d p_;
//  //      // p_[0] = p3d[i][0];
//  //      // p_[1] = p3d[i][1];
//  //      // p_[2] = p3d[i][2];
//  //      // p_[3] = 1;
//  //      // Vector4d p_prime4 = T_esti.matrix() * p_; // T的矩阵是4x4
//  //      // cout << "p_prime4 = " << p_prime4 << endl;
//  //      // END YOUR CODE HERE
//  //
//  //      // compute jacobian
//  //      Matrix<double, 2, 6> J;
//  //      // START YOUR CODE HERE
//  //      // 得到3d到2d投影点
//  //      Vector3d p_prime_norm(p_prime[0] / p_prime[2], p_prime[1] /
//  //      p_prime[2],
//  //                            1); // 归一化p'，方便K计算投影
//  //      Vector3d p_prime_2d = K * p_prime_norm; // p'的投影的齐次形式
//  //      // cout << "p_prime_2d " << p_prime_2d << endl;
//  //
//  //      // 得到投影结果的重投影误差
//  //      Vector2d e; // e是由x y共同组成的，所以是二维
//  //      e[0] = p2d[i][0] - p_prime_2d[0];         // x坐标重投影误差
//  //      e[1] = p2d[i][1] - p_prime_2d[1];         // y坐标重投影误差
//  //      cost = sqrt(pow(e[0], 2) + pow(e[1], 2)); // 生成cost
//  //      // cout << "e1 " << e[0] << "   e2 " << e[1] << endl;
//  //
//  //      // 根据公式得到J (2 x 6的维度)  de/dxi
//  //      double X_(p_prime[0]), Y_(p_prime[1]), Z_(p_prime[2]);
//  //      J(0, 0) = -fx / Z_;
//  //      J(0, 1) = 0;
//  //      J(0, 2) = fx * X_ / pow(Z_, 2);
//  //      J(0, 3) = fx * X_ * Y_ / pow(Z_, 2);
//  //      J(0, 4) = -fx - fx * pow(X_, 2) / pow(Z_, 2);
//  //      J(0, 5) = fx * Y_ / Z_;
//  //      J(1, 0) = 0;
//  //      J(1, 1) = -fy / Z_;
//  //      J(1, 2) = fy * Y_ / pow(Z_, 2);
//  //      J(1, 3) = fy + fy * pow(Y_, 2) / pow(Z_, 2);
//  //      J(1, 4) = -fy * X_ * Y_ / pow(Z_, 2);
//  //      J(1, 5) = -fy * X_ / Z_;
//  //      // END YOUR CODE HERE
//  //
//  //      H += J.transpose() * J;
//  //      b += -J.transpose() * e;
//  //    }
//  //
//  //    // solve dx
//  //    Vector6d dx;
//  //
//  //    // START YOUR CODE HERE
//  //    dx = H.ldlt().solve(b); // 使用经典的LDLT分解法解方程
//  //    // END YOUR CODE HERE
//  //
//  //    if (isnan(dx[0])) {
//  //      cout << "result is nan!" << endl;
//  //      break;
//  //    }
//  //
//  //    if (iter > 0 && cost >= lastCost) {
//  //      // cost increase, update is not good
//  //      cout << "cost: " << cost << ", last cost: " << lastCost << endl;
//  //      // break;
//  //    }
//  //
//  //    // update your estimation
//  //    // START YOUR CODE HERE
//  //    Vector6d T_esti_se3 = T_esti.log(); // 构造李代数
//  //    T_esti_se3 += dx;                   // 更新李代数se3
//  //    T_esti = Sophus::SE3::exp(
//  //        T_esti_se3); // 不必使用反对称的se3(SE3::hat可以构造反对称)
//  //    // cout << "T_esti_updated: " << T_esti.matrix() << endl;
//  //    // END YOUR CODE HERE
//  //
//  //    lastCost = cost;
//  //
//  //    cout << "iteration " << iter << " cost=" << cout.precision(12) << cost
//  //         << endl;
//  //  }
//  //
//  //  cout << "estimated pose: \n" << T_esti.matrix() << endl;
//
//  // Now we are trying the ICP mode.
//
//  // 定义点集合
//  vector<Eigen::Vector3d> pi_g, pi_e;
//
//  for (int k = 0; k < matches.size(); ++k) {
//    pi_g.emplace_back(depth_points[matches[k].queryIdx].x,
//                      depth_points[matches[k].queryIdx].y,
//                      depth_points[matches[k].queryIdx].z);
//    pi_e.emplace_back(depth_points2[matches[k].trainIdx].x,
//                      depth_points2[matches[k].trainIdx].y,
//                      depth_points2[matches[k].trainIdx].z);
//  }
//
//  DrawTrace(pi_g, pi_e, "init");
//
//  // 由于轨迹点都是Twc，按书上定义是C到W(世界坐标)下，所以这里的每个t就是该点在世界坐标系下的坐标了
//  // 求取点坐标集合和质心操作
//  Eigen::Vector3d p_gc(0, 0, 0), p_ec(0, 0, 0);
//  for (auto p : pi_g) {
//    p_gc += p / static_cast<double>(pi_g.size());
//  }
//
//  for (auto p : pi_e) {
//    p_ec += p / static_cast<double>(pi_e.size());
//  }
//  // cout << "Gc: "<< p_gc << "   Ec: " << p_ec << endl;
//
//  // 定义去质心坐标
//  vector<Eigen::Vector3d> qi_g, qi_e;
//  for (auto p : pi_g) {
//    qi_g.emplace_back(p - p_gc);
//  }
//
//  for (auto p : pi_e) {
//    qi_e.emplace_back(p - p_ec);
//  }
//
//  // 计算W
//  Eigen::Matrix3d W;               // 等价于 Eigen::Matrix<double, 3, 3>
//  W = Eigen::Matrix3d::Zero(3, 3); // 初始化为0
//  // cout << "W : " << W << endl;
//  for (int i = 0; i < qi_g.size(); ++i) {
//    W += qi_g[i] * qi_e[i].transpose(); // 累加求得W
//  }
//  // cout << "W : " << W << endl;
//
//  // SVD 解法
//  Eigen::JacobiSVD<Eigen::MatrixXd> svd(
//      W, Eigen::ComputeFullV |
//             Eigen::ComputeFullU); // ComputeFull vs ComputeThin 是不同的
//  Eigen::MatrixXd U = svd.matrixU();
//  Eigen::MatrixXd V = svd.matrixV();
//
//  Eigen::MatrixXd R = U * V.transpose(); // 计算得到R
//  cout << "R: " << R << endl;
//
//  // 通过令第二项最小值为0，生成t
//  Eigen::Vector3d t = p_gc - R * p_ec;
//  cout << "t: " << t << endl;
//
//  // 将e变换到g下(注意Tge是将e变换到g，所以t也不用取反是正确的)，更新每个点的坐标，再重新画图
//  for (auto &p : pi_e) {
//    p = R * p + t;
//  }
//
//  DrawTrace(pi_g, pi_e, "end");
//
//  return 0;
//}
//
//void showPointCloud(
//    const vector<Vector4d, Eigen::aligned_allocator<Vector4d>> &pointcloud) {
//
//  if (pointcloud.empty()) {
//    cerr << "Point cloud is empty!" << endl;
//    return;
//  }
//
//  pangolin::CreateWindowAndBind("Point Cloud Viewer", 1024, 768);
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//  pangolin::OpenGlRenderState s_cam(
//      pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
//      pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));
//
//  pangolin::View &d_cam = pangolin::CreateDisplay()
//                              .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175),
//                                         1.0, -1024.0f / 768.0f)
//                              .SetHandler(new pangolin::Handler3D(s_cam));
//
//  while (pangolin::ShouldQuit() == false) {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    d_cam.Activate(s_cam);
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    glPointSize(2);
//    glBegin(GL_POINTS);
//    for (auto &p : pointcloud) {
//      glColor3f(p[3], p[3], p[3]);
//      glVertex3d(p[0], p[1], p[2]);
//    }
//    glEnd();
//    pangolin::FinishFrame();
//    usleep(5000); // sleep 5 ms
//  }
//  return;
//}
//
//// BilinearInterpolation for accurate depth of feature point.
//// Return depth.
//float findDepth(const cv::Mat &depth_image, const cv::Point2f &point) {
//  float fy = (float)((point.y + 0.5) * 1.0f - 0.5);
//  int sy = (int)fy - ((int)fy > fy);
//  fy -= sy;
//
//  if (sy < 0) {
//    return -1;
//  }
//  if (sy >= depth_image.rows - 1) {
//    return -1;
//  }
//
//  float coefy[2];
//  coefy[0] = 1.f - fy;
//  coefy[1] = fy;
//
//  float fx = (float)((point.x + 0.5) * 1.0f - 0.5);
//  int sx = (int)fx - ((int)fx > fx);
//  fx -= sx;
//
//  if (sx < 0) {
//    return -1;
//  }
//  if (sx >= depth_image.cols - 1) {
//    return -1;
//  }
//
//  float coefx[2];
//  coefx[0] = 1.f - fx;
//  coefx[1] = fx;
//
//  float tl = coefx[0] * coefy[0] * depth_image.at<float>(sy, sx);
//  float tr =
//      fx == 0 ? 0 : coefx[1] * coefy[0] * depth_image.at<float>(sy, sx + 1);
//  float dl =
//      fy == 0 ? 0 : coefx[0] * coefy[1] * depth_image.at<float>(sy + 1, sx);
//  float dr = fy == 0 || fx == 0
//                 ? 0
//                 : coefx[1] * coefy[1] * depth_image.at<float>(sy + 1, sx + 1);
//
//  if (tl > 0 || tr > 0 || dl > 0 || dr > 0) {
//    return tl + tr + dl + dr;
//  } else
//    return -1;
//}
//
//// -------------------------------------------------------------------------- //
//// --------------------------------------------------------------------------------------------------
//// //
//
//// compute the angle
//void computeAngle(const cv::Mat &image, vector<cv::KeyPoint> &keypoints) {
//  int half_patch_size = 8;
//  for (auto &kp : keypoints) {
//    // START YOUR CODE HERE (~7 lines)
//    kp.angle = 0; // compute kp.angle
//    if ((kp.pt.x < half_patch_size) || (kp.pt.y < half_patch_size) ||
//        (kp.pt.x > (image.cols - half_patch_size)) ||
//        (kp.pt.y > (image.rows - half_patch_size)))
//      continue; // 判断范围，如果能用去除vector可能更严谨一些
//    else {
//      double m01(0), m10(0); // 初始化矩
//      for (int du = -half_patch_size; du < half_patch_size; ++du) {
//        for (int dv = -half_patch_size; dv < half_patch_size; ++dv) {
//          m01 += static_cast<double>(
//              (dv)*image.at<uchar>(kp.pt.y + dv, kp.pt.x + du)); // 公式计算
//          m10 += static_cast<double>(
//              (du)*image.at<uchar>(kp.pt.y + dv, kp.pt.x + du));
//        }
//      }
//      kp.angle =
//          atan2(m01, m10) / pi *
//          180.0; // 角度弧度转换,
//                 // atan2(y,x)可以对应360度完整的角度空间，而atan(y/x)则要麻烦一些
//    }
//    // END YOUR CODE HERE
//  }
//  return;
//}
//
//// --------------------------------------------------------------------------------------------------
//// // ORB pattern
//int ORB_pattern[256 * 4] = {
//    8,   -3,  9,   5 /*mean (0), correlation (0)*/,
//    4,   2,   7,   -12 /*mean (1.12461e-05), correlation (0.0437584)*/,
//    -11, 9,   -8,  2 /*mean (3.37382e-05), correlation (0.0617409)*/,
//    7,   -12, 12,  -13 /*mean (5.62303e-05), correlation (0.0636977)*/,
//    2,   -13, 2,   12 /*mean (0.000134953), correlation (0.085099)*/,
//    1,   -7,  1,   6 /*mean (0.000528565), correlation (0.0857175)*/,
//    -2,  -10, -2,  -4 /*mean (0.0188821), correlation (0.0985774)*/,
//    -13, -13, -11, -8 /*mean (0.0363135), correlation (0.0899616)*/,
//    -13, -3,  -12, -9 /*mean (0.121806), correlation (0.099849)*/,
//    10,  4,   11,  9 /*mean (0.122065), correlation (0.093285)*/,
//    -13, -8,  -8,  -9 /*mean (0.162787), correlation (0.0942748)*/,
//    -11, 7,   -9,  12 /*mean (0.21561), correlation (0.0974438)*/,
//    7,   7,   12,  6 /*mean (0.160583), correlation (0.130064)*/,
//    -4,  -5,  -3,  0 /*mean (0.228171), correlation (0.132998)*/,
//    -13, 2,   -12, -3 /*mean (0.00997526), correlation (0.145926)*/,
//    -9,  0,   -7,  5 /*mean (0.198234), correlation (0.143636)*/,
//    12,  -6,  12,  -1 /*mean (0.0676226), correlation (0.16689)*/,
//    -3,  6,   -2,  12 /*mean (0.166847), correlation (0.171682)*/,
//    -6,  -13, -4,  -8 /*mean (0.101215), correlation (0.179716)*/,
//    11,  -13, 12,  -8 /*mean (0.200641), correlation (0.192279)*/,
//    4,   7,   5,   1 /*mean (0.205106), correlation (0.186848)*/,
//    5,   -3,  10,  -3 /*mean (0.234908), correlation (0.192319)*/,
//    3,   -7,  6,   12 /*mean (0.0709964), correlation (0.210872)*/,
//    -8,  -7,  -6,  -2 /*mean (0.0939834), correlation (0.212589)*/,
//    -2,  11,  -1,  -10 /*mean (0.127778), correlation (0.20866)*/,
//    -13, 12,  -8,  10 /*mean (0.14783), correlation (0.206356)*/,
//    -7,  3,   -5,  -3 /*mean (0.182141), correlation (0.198942)*/,
//    -4,  2,   -3,  7 /*mean (0.188237), correlation (0.21384)*/,
//    -10, -12, -6,  11 /*mean (0.14865), correlation (0.23571)*/,
//    5,   -12, 6,   -7 /*mean (0.222312), correlation (0.23324)*/,
//    5,   -6,  7,   -1 /*mean (0.229082), correlation (0.23389)*/,
//    1,   0,   4,   -5 /*mean (0.241577), correlation (0.215286)*/,
//    9,   11,  11,  -13 /*mean (0.00338507), correlation (0.251373)*/,
//    4,   7,   4,   12 /*mean (0.131005), correlation (0.257622)*/,
//    2,   -1,  4,   4 /*mean (0.152755), correlation (0.255205)*/,
//    -4,  -12, -2,  7 /*mean (0.182771), correlation (0.244867)*/,
//    -8,  -5,  -7,  -10 /*mean (0.186898), correlation (0.23901)*/,
//    4,   11,  9,   12 /*mean (0.226226), correlation (0.258255)*/,
//    0,   -8,  1,   -13 /*mean (0.0897886), correlation (0.274827)*/,
//    -13, -2,  -8,  2 /*mean (0.148774), correlation (0.28065)*/,
//    -3,  -2,  -2,  3 /*mean (0.153048), correlation (0.283063)*/,
//    -6,  9,   -4,  -9 /*mean (0.169523), correlation (0.278248)*/,
//    8,   12,  10,  7 /*mean (0.225337), correlation (0.282851)*/,
//    0,   9,   1,   3 /*mean (0.226687), correlation (0.278734)*/,
//    7,   -5,  11,  -10 /*mean (0.00693882), correlation (0.305161)*/,
//    -13, -6,  -11, 0 /*mean (0.0227283), correlation (0.300181)*/,
//    10,  7,   12,  1 /*mean (0.125517), correlation (0.31089)*/,
//    -6,  -3,  -6,  12 /*mean (0.131748), correlation (0.312779)*/,
//    10,  -9,  12,  -4 /*mean (0.144827), correlation (0.292797)*/,
//    -13, 8,   -8,  -12 /*mean (0.149202), correlation (0.308918)*/,
//    -13, 0,   -8,  -4 /*mean (0.160909), correlation (0.310013)*/,
//    3,   3,   7,   8 /*mean (0.177755), correlation (0.309394)*/,
//    5,   7,   10,  -7 /*mean (0.212337), correlation (0.310315)*/,
//    -1,  7,   1,   -12 /*mean (0.214429), correlation (0.311933)*/,
//    3,   -10, 5,   6 /*mean (0.235807), correlation (0.313104)*/,
//    2,   -4,  3,   -10 /*mean (0.00494827), correlation (0.344948)*/,
//    -13, 0,   -13, 5 /*mean (0.0549145), correlation (0.344675)*/,
//    -13, -7,  -12, 12 /*mean (0.103385), correlation (0.342715)*/,
//    -13, 3,   -11, 8 /*mean (0.134222), correlation (0.322922)*/,
//    -7,  12,  -4,  7 /*mean (0.153284), correlation (0.337061)*/,
//    6,   -10, 12,  8 /*mean (0.154881), correlation (0.329257)*/,
//    -9,  -1,  -7,  -6 /*mean (0.200967), correlation (0.33312)*/,
//    -2,  -5,  0,   12 /*mean (0.201518), correlation (0.340635)*/,
//    -12, 5,   -7,  5 /*mean (0.207805), correlation (0.335631)*/,
//    3,   -10, 8,   -13 /*mean (0.224438), correlation (0.34504)*/,
//    -7,  -7,  -4,  5 /*mean (0.239361), correlation (0.338053)*/,
//    -3,  -2,  -1,  -7 /*mean (0.240744), correlation (0.344322)*/,
//    2,   9,   5,   -11 /*mean (0.242949), correlation (0.34145)*/,
//    -11, -13, -5,  -13 /*mean (0.244028), correlation (0.336861)*/,
//    -1,  6,   0,   -1 /*mean (0.247571), correlation (0.343684)*/,
//    5,   -3,  5,   2 /*mean (0.000697256), correlation (0.357265)*/,
//    -4,  -13, -4,  12 /*mean (0.00213675), correlation (0.373827)*/,
//    -9,  -6,  -9,  6 /*mean (0.0126856), correlation (0.373938)*/,
//    -12, -10, -8,  -4 /*mean (0.0152497), correlation (0.364237)*/,
//    10,  2,   12,  -3 /*mean (0.0299933), correlation (0.345292)*/,
//    7,   12,  12,  12 /*mean (0.0307242), correlation (0.366299)*/,
//    -7,  -13, -6,  5 /*mean (0.0534975), correlation (0.368357)*/,
//    -4,  9,   -3,  4 /*mean (0.099865), correlation (0.372276)*/,
//    7,   -1,  12,  2 /*mean (0.117083), correlation (0.364529)*/,
//    -7,  6,   -5,  1 /*mean (0.126125), correlation (0.369606)*/,
//    -13, 11,  -12, 5 /*mean (0.130364), correlation (0.358502)*/,
//    -3,  7,   -2,  -6 /*mean (0.131691), correlation (0.375531)*/,
//    7,   -8,  12,  -7 /*mean (0.160166), correlation (0.379508)*/,
//    -13, -7,  -11, -12 /*mean (0.167848), correlation (0.353343)*/,
//    1,   -3,  12,  12 /*mean (0.183378), correlation (0.371916)*/,
//    2,   -6,  3,   0 /*mean (0.228711), correlation (0.371761)*/,
//    -4,  3,   -2,  -13 /*mean (0.247211), correlation (0.364063)*/,
//    -1,  -13, 1,   9 /*mean (0.249325), correlation (0.378139)*/,
//    7,   1,   8,   -6 /*mean (0.000652272), correlation (0.411682)*/,
//    1,   -1,  3,   12 /*mean (0.00248538), correlation (0.392988)*/,
//    9,   1,   12,  6 /*mean (0.0206815), correlation (0.386106)*/,
//    -1,  -9,  -1,  3 /*mean (0.0364485), correlation (0.410752)*/,
//    -13, -13, -10, 5 /*mean (0.0376068), correlation (0.398374)*/,
//    7,   7,   10,  12 /*mean (0.0424202), correlation (0.405663)*/,
//    12,  -5,  12,  9 /*mean (0.0942645), correlation (0.410422)*/,
//    6,   3,   7,   11 /*mean (0.1074), correlation (0.413224)*/,
//    5,   -13, 6,   10 /*mean (0.109256), correlation (0.408646)*/,
//    2,   -12, 2,   3 /*mean (0.131691), correlation (0.416076)*/,
//    3,   8,   4,   -6 /*mean (0.165081), correlation (0.417569)*/,
//    2,   6,   12,  -13 /*mean (0.171874), correlation (0.408471)*/,
//    9,   -12, 10,  3 /*mean (0.175146), correlation (0.41296)*/,
//    -8,  4,   -7,  9 /*mean (0.183682), correlation (0.402956)*/,
//    -11, 12,  -4,  -6 /*mean (0.184672), correlation (0.416125)*/,
//    1,   12,  2,   -8 /*mean (0.191487), correlation (0.386696)*/,
//    6,   -9,  7,   -4 /*mean (0.192668), correlation (0.394771)*/,
//    2,   3,   3,   -2 /*mean (0.200157), correlation (0.408303)*/,
//    6,   3,   11,  0 /*mean (0.204588), correlation (0.411762)*/,
//    3,   -3,  8,   -8 /*mean (0.205904), correlation (0.416294)*/,
//    7,   8,   9,   3 /*mean (0.213237), correlation (0.409306)*/,
//    -11, -5,  -6,  -4 /*mean (0.243444), correlation (0.395069)*/,
//    -10, 11,  -5,  10 /*mean (0.247672), correlation (0.413392)*/,
//    -5,  -8,  -3,  12 /*mean (0.24774), correlation (0.411416)*/,
//    -10, 5,   -9,  0 /*mean (0.00213675), correlation (0.454003)*/,
//    8,   -1,  12,  -6 /*mean (0.0293635), correlation (0.455368)*/,
//    4,   -6,  6,   -11 /*mean (0.0404971), correlation (0.457393)*/,
//    -10, 12,  -8,  7 /*mean (0.0481107), correlation (0.448364)*/,
//    4,   -2,  6,   7 /*mean (0.050641), correlation (0.455019)*/,
//    -2,  0,   -2,  12 /*mean (0.0525978), correlation (0.44338)*/,
//    -5,  -8,  -5,  2 /*mean (0.0629667), correlation (0.457096)*/,
//    7,   -6,  10,  12 /*mean (0.0653846), correlation (0.445623)*/,
//    -9,  -13, -8,  -8 /*mean (0.0858749), correlation (0.449789)*/,
//    -5,  -13, -5,  -2 /*mean (0.122402), correlation (0.450201)*/,
//    8,   -8,  9,   -13 /*mean (0.125416), correlation (0.453224)*/,
//    -9,  -11, -9,  0 /*mean (0.130128), correlation (0.458724)*/,
//    1,   -8,  1,   -2 /*mean (0.132467), correlation (0.440133)*/,
//    7,   -4,  9,   1 /*mean (0.132692), correlation (0.454)*/,
//    -2,  1,   -1,  -4 /*mean (0.135695), correlation (0.455739)*/,
//    11,  -6,  12,  -11 /*mean (0.142904), correlation (0.446114)*/,
//    -12, -9,  -6,  4 /*mean (0.146165), correlation (0.451473)*/,
//    3,   7,   7,   12 /*mean (0.147627), correlation (0.456643)*/,
//    5,   5,   10,  8 /*mean (0.152901), correlation (0.455036)*/,
//    0,   -4,  2,   8 /*mean (0.167083), correlation (0.459315)*/,
//    -9,  12,  -5,  -13 /*mean (0.173234), correlation (0.454706)*/,
//    0,   7,   2,   12 /*mean (0.18312), correlation (0.433855)*/,
//    -1,  2,   1,   7 /*mean (0.185504), correlation (0.443838)*/,
//    5,   11,  7,   -9 /*mean (0.185706), correlation (0.451123)*/,
//    3,   5,   6,   -8 /*mean (0.188968), correlation (0.455808)*/,
//    -13, -4,  -8,  9 /*mean (0.191667), correlation (0.459128)*/,
//    -5,  9,   -3,  -3 /*mean (0.193196), correlation (0.458364)*/,
//    -4,  -7,  -3,  -12 /*mean (0.196536), correlation (0.455782)*/,
//    6,   5,   8,   0 /*mean (0.1972), correlation (0.450481)*/,
//    -7,  6,   -6,  12 /*mean (0.199438), correlation (0.458156)*/,
//    -13, 6,   -5,  -2 /*mean (0.211224), correlation (0.449548)*/,
//    1,   -10, 3,   10 /*mean (0.211718), correlation (0.440606)*/,
//    4,   1,   8,   -4 /*mean (0.213034), correlation (0.443177)*/,
//    -2,  -2,  2,   -13 /*mean (0.234334), correlation (0.455304)*/,
//    2,   -12, 12,  12 /*mean (0.235684), correlation (0.443436)*/,
//    -2,  -13, 0,   -6 /*mean (0.237674), correlation (0.452525)*/,
//    4,   1,   9,   3 /*mean (0.23962), correlation (0.444824)*/,
//    -6,  -10, -3,  -5 /*mean (0.248459), correlation (0.439621)*/,
//    -3,  -13, -1,  1 /*mean (0.249505), correlation (0.456666)*/,
//    7,   5,   12,  -11 /*mean (0.00119208), correlation (0.495466)*/,
//    4,   -2,  5,   -7 /*mean (0.00372245), correlation (0.484214)*/,
//    -13, 9,   -9,  -5 /*mean (0.00741116), correlation (0.499854)*/,
//    7,   1,   8,   6 /*mean (0.0208952), correlation (0.499773)*/,
//    7,   -8,  7,   6 /*mean (0.0220085), correlation (0.501609)*/,
//    -7,  -4,  -7,  1 /*mean (0.0233806), correlation (0.496568)*/,
//    -8,  11,  -7,  -8 /*mean (0.0236505), correlation (0.489719)*/,
//    -13, 6,   -12, -8 /*mean (0.0268781), correlation (0.503487)*/,
//    2,   4,   3,   9 /*mean (0.0323324), correlation (0.501938)*/,
//    10,  -5,  12,  3 /*mean (0.0399235), correlation (0.494029)*/,
//    -6,  -5,  -6,  7 /*mean (0.0420153), correlation (0.486579)*/,
//    8,   -3,  9,   -8 /*mean (0.0548021), correlation (0.484237)*/,
//    2,   -12, 2,   8 /*mean (0.0616622), correlation (0.496642)*/,
//    -11, -2,  -10, 3 /*mean (0.0627755), correlation (0.498563)*/,
//    -12, -13, -7,  -9 /*mean (0.0829622), correlation (0.495491)*/,
//    -11, 0,   -10, -5 /*mean (0.0843342), correlation (0.487146)*/,
//    5,   -3,  11,  8 /*mean (0.0929937), correlation (0.502315)*/,
//    -2,  -13, -1,  12 /*mean (0.113327), correlation (0.48941)*/,
//    -1,  -8,  0,   9 /*mean (0.132119), correlation (0.467268)*/,
//    -13, -11, -12, -5 /*mean (0.136269), correlation (0.498771)*/,
//    -10, -2,  -10, 11 /*mean (0.142173), correlation (0.498714)*/,
//    -3,  9,   -2,  -13 /*mean (0.144141), correlation (0.491973)*/,
//    2,   -3,  3,   2 /*mean (0.14892), correlation (0.500782)*/,
//    -9,  -13, -4,  0 /*mean (0.150371), correlation (0.498211)*/,
//    -4,  6,   -3,  -10 /*mean (0.152159), correlation (0.495547)*/,
//    -4,  12,  -2,  -7 /*mean (0.156152), correlation (0.496925)*/,
//    -6,  -11, -4,  9 /*mean (0.15749), correlation (0.499222)*/,
//    6,   -3,  6,   11 /*mean (0.159211), correlation (0.503821)*/,
//    -13, 11,  -5,  5 /*mean (0.162427), correlation (0.501907)*/,
//    11,  11,  12,  6 /*mean (0.16652), correlation (0.497632)*/,
//    7,   -5,  12,  -2 /*mean (0.169141), correlation (0.484474)*/,
//    -1,  12,  0,   7 /*mean (0.169456), correlation (0.495339)*/,
//    -4,  -8,  -3,  -2 /*mean (0.171457), correlation (0.487251)*/,
//    -7,  1,   -6,  7 /*mean (0.175), correlation (0.500024)*/,
//    -13, -12, -8,  -13 /*mean (0.175866), correlation (0.497523)*/,
//    -7,  -2,  -6,  -8 /*mean (0.178273), correlation (0.501854)*/,
//    -8,  5,   -6,  -9 /*mean (0.181107), correlation (0.494888)*/,
//    -5,  -1,  -4,  5 /*mean (0.190227), correlation (0.482557)*/,
//    -13, 7,   -8,  10 /*mean (0.196739), correlation (0.496503)*/,
//    1,   5,   5,   -13 /*mean (0.19973), correlation (0.499759)*/,
//    1,   0,   10,  -13 /*mean (0.204465), correlation (0.49873)*/,
//    9,   12,  10,  -1 /*mean (0.209334), correlation (0.49063)*/,
//    5,   -8,  10,  -9 /*mean (0.211134), correlation (0.503011)*/,
//    -1,  11,  1,   -13 /*mean (0.212), correlation (0.499414)*/,
//    -9,  -3,  -6,  2 /*mean (0.212168), correlation (0.480739)*/,
//    -1,  -10, 1,   12 /*mean (0.212731), correlation (0.502523)*/,
//    -13, 1,   -8,  -10 /*mean (0.21327), correlation (0.489786)*/,
//    8,   -11, 10,  -6 /*mean (0.214159), correlation (0.488246)*/,
//    2,   -13, 3,   -6 /*mean (0.216993), correlation (0.50287)*/,
//    7,   -13, 12,  -9 /*mean (0.223639), correlation (0.470502)*/,
//    -10, -10, -5,  -7 /*mean (0.224089), correlation (0.500852)*/,
//    -10, -8,  -8,  -13 /*mean (0.228666), correlation (0.502629)*/,
//    4,   -6,  8,   5 /*mean (0.22906), correlation (0.498305)*/,
//    3,   12,  8,   -13 /*mean (0.233378), correlation (0.503825)*/,
//    -4,  2,   -3,  -3 /*mean (0.234323), correlation (0.476692)*/,
//    5,   -13, 10,  -12 /*mean (0.236392), correlation (0.475462)*/,
//    4,   -13, 5,   -1 /*mean (0.236842), correlation (0.504132)*/,
//    -9,  9,   -4,  3 /*mean (0.236977), correlation (0.497739)*/,
//    0,   3,   3,   -9 /*mean (0.24314), correlation (0.499398)*/,
//    -12, 1,   -6,  1 /*mean (0.243297), correlation (0.489447)*/,
//    3,   2,   4,   -8 /*mean (0.00155196), correlation (0.553496)*/,
//    -10, -10, -10, 9 /*mean (0.00239541), correlation (0.54297)*/,
//    8,   -13, 12,  12 /*mean (0.0034413), correlation (0.544361)*/,
//    -8,  -12, -6,  -5 /*mean (0.003565), correlation (0.551225)*/,
//    2,   2,   3,   7 /*mean (0.00835583), correlation (0.55285)*/,
//    10,  6,   11,  -8 /*mean (0.00885065), correlation (0.540913)*/,
//    6,   8,   8,   -12 /*mean (0.0101552), correlation (0.551085)*/,
//    -7,  10,  -6,  5 /*mean (0.0102227), correlation (0.533635)*/,
//    -3,  -9,  -3,  9 /*mean (0.0110211), correlation (0.543121)*/,
//    -1,  -13, -1,  5 /*mean (0.0113473), correlation (0.550173)*/,
//    -3,  -7,  -3,  4 /*mean (0.0140913), correlation (0.554774)*/,
//    -8,  -2,  -8,  3 /*mean (0.017049), correlation (0.55461)*/,
//    4,   2,   12,  12 /*mean (0.01778), correlation (0.546921)*/,
//    2,   -5,  3,   11 /*mean (0.0224022), correlation (0.549667)*/,
//    6,   -9,  11,  -13 /*mean (0.029161), correlation (0.546295)*/,
//    3,   -1,  7,   12 /*mean (0.0303081), correlation (0.548599)*/,
//    11,  -1,  12,  4 /*mean (0.0355151), correlation (0.523943)*/,
//    -3,  0,   -3,  6 /*mean (0.0417904), correlation (0.543395)*/,
//    4,   -11, 4,   12 /*mean (0.0487292), correlation (0.542818)*/,
//    2,   -4,  2,   1 /*mean (0.0575124), correlation (0.554888)*/,
//    -10, -6,  -8,  1 /*mean (0.0594242), correlation (0.544026)*/,
//    -13, 7,   -11, 1 /*mean (0.0597391), correlation (0.550524)*/,
//    -13, 12,  -11, -13 /*mean (0.0608974), correlation (0.55383)*/,
//    6,   0,   11,  -13 /*mean (0.065126), correlation (0.552006)*/,
//    0,   -1,  1,   4 /*mean (0.074224), correlation (0.546372)*/,
//    -13, 3,   -9,  -2 /*mean (0.0808592), correlation (0.554875)*/,
//    -9,  8,   -6,  -3 /*mean (0.0883378), correlation (0.551178)*/,
//    -13, -6,  -8,  -2 /*mean (0.0901035), correlation (0.548446)*/,
//    5,   -9,  8,   10 /*mean (0.0949843), correlation (0.554694)*/,
//    2,   7,   3,   -9 /*mean (0.0994152), correlation (0.550979)*/,
//    -1,  -6,  -1,  -1 /*mean (0.10045), correlation (0.552714)*/,
//    9,   5,   11,  -2 /*mean (0.100686), correlation (0.552594)*/,
//    11,  -3,  12,  -8 /*mean (0.101091), correlation (0.532394)*/,
//    3,   0,   3,   5 /*mean (0.101147), correlation (0.525576)*/,
//    -1,  4,   0,   10 /*mean (0.105263), correlation (0.531498)*/,
//    3,   -6,  4,   5 /*mean (0.110785), correlation (0.540491)*/,
//    -13, 0,   -10, 5 /*mean (0.112798), correlation (0.536582)*/,
//    5,   8,   12,  11 /*mean (0.114181), correlation (0.555793)*/,
//    8,   9,   9,   -6 /*mean (0.117431), correlation (0.553763)*/,
//    7,   -4,  8,   -12 /*mean (0.118522), correlation (0.553452)*/,
//    -10, 4,   -10, 9 /*mean (0.12094), correlation (0.554785)*/,
//    7,   3,   12,  4 /*mean (0.122582), correlation (0.555825)*/,
//    9,   -7,  10,  -2 /*mean (0.124978), correlation (0.549846)*/,
//    7,   0,   12,  -2 /*mean (0.127002), correlation (0.537452)*/,
//    -1,  -6,  0,   -11 /*mean (0.127148), correlation (0.547401)*/
//};
//
//// compute the descriptor
//void computeORBDesc(const cv::Mat &image, vector<cv::KeyPoint> &keypoints,
//                    vector<DescType> &desc) {
//  for (auto &kp : keypoints) {
//    DescType d(256, false);
//    for (int i = 0; i < 256; i++) {
//      // START YOUR CODE HERE (~7 lines)
//      float angle_rad(kp.angle / 180.0f * pi); // 注意弧度角度转换
//      float ppu(cos(angle_rad) * ORB_pattern[i * 4] -
//                sin(angle_rad) * ORB_pattern[i * 4 + 1]),
//          ppv(sin(angle_rad) * ORB_pattern[i * 4] +
//              cos(angle_rad) * ORB_pattern[i * 4 + 1]),
//          qpu(cos(angle_rad) * ORB_pattern[i * 4 + 2] -
//              sin(angle_rad) * ORB_pattern[i * 4 + 3]),
//          qpv(sin(angle_rad) * ORB_pattern[i * 4 + 2] +
//              cos(angle_rad) * ORB_pattern[i * 4 + 3]); // 参考公式生成坐标值
//      if ((kp.pt.x + ORB_pattern[i * 4]) < 0 ||
//          (kp.pt.x + ORB_pattern[i * 4 + 2]) < 0 || (kp.pt.x + ppu) < 0 ||
//          (kp.pt.x + qpu) < 0 ||
//          (kp.pt.x + ORB_pattern[i * 4]) > (image.cols - 1) ||
//          (kp.pt.x + ORB_pattern[i * 4 + 2]) > (image.cols - 1) ||
//          (kp.pt.x + ppu) > (image.cols - 1) ||
//          (kp.pt.x + qpu) > (image.cols - 1) ||
//          (kp.pt.y + ORB_pattern[i * 4 + 1]) < 0 ||
//          (kp.pt.y + ORB_pattern[i * 4 + 3]) < 0 || (kp.pt.y + ppv) < 0 ||
//          (kp.pt.y + qpv) < 0 ||
//          (kp.pt.y + ORB_pattern[i * 4 + 1]) > (image.rows - 1) ||
//          (kp.pt.y + ORB_pattern[i * 4 + 3]) > (image.rows - 1) ||
//          (kp.pt.y + ppv) > (image.rows - 1) ||
//          (kp.pt.y + qpv) > (image.rows - 1)) {
//        d.clear(); // if kp goes outside, set d.clear()
//        break;
//      }
//      d[i] = image.at<uchar>(kp.pt.y + ppv, kp.pt.x + ppu) >
//                     image.at<uchar>(kp.pt.y + qpv, kp.pt.x + qpu)
//                 ? 0
//                 : 1; // 采用三目运算符比较大小
//                      // END YOUR CODE HERE
//    }
//    desc.push_back(d);
//  }
//
//  int bad = 0;
//  for (auto &d : desc) {
//    if (d.empty())
//      bad++;
//  }
//  cout << "bad/total: " << bad << "/" << desc.size() << endl;
//  return;
//}
//
//// brute-force matching
//void bfMatch(const vector<DescType> &desc1, const vector<DescType> &desc2,
//             vector<cv::DMatch> &matches) {
//  int d_max = 50;
//
//  // START YOUR CODE HERE (~12 lines)
//  // find matches between desc1 and desc2.
//  for (int i = 0; i < desc1.size(); ++i) {
//    if (desc1[i].size() == 0)
//      continue; // 判断输入的特征是否有效，无效则跳过
//    else {
//      int idx(-1), dist(256);
//      for (int j = 0; j < desc2.size(); ++j) {
//        if (desc2[j].size() == 0)
//          continue; // 判断待匹配点的特征是否有效，无效则跳过
//        else {
//          int this_dist(0);
//          for (int k = 0; k < 256; ++k)
//            if (desc1[i][k] != desc2[j][k])
//              this_dist++;                              // 汉明距离
//          if (this_dist <= d_max && this_dist < dist) { // 阈值判断
//            dist = this_dist;
//            idx = j;
//          }
//        }
//      }
//      if (idx != -1) { // 填充匹配成功的关键点对
//        cv::DMatch m;
//        m.queryIdx = i;
//        m.trainIdx = idx;
//        m.distance = dist;
//        matches.push_back(m);
//      }
//    }
//  }
//
//  // END YOUR CODE HERE
//
//  for (auto &m : matches) {
//    cout << m.queryIdx << ", " << m.trainIdx << ", " << m.distance << endl;
//  }
//  return;
//}
//
///*******************************************************************************************/
//bool DrawTrace(const vector<Eigen::Vector3d> &pi_g,
//               const vector<Eigen::Vector3d> &pi_e, const string &name) {
//  if (pi_g.empty() || pi_e.empty()) {
//    cerr << "Ground truth or estimation trace is empty!" << endl;
//    return false;
//  }
//
//  if (pi_g.size() != pi_e.size()) {
//    cerr << "Ground truth and estimation dimension mismatch!" << endl;
//    return false;
//  }
//
//  // create pangolin window and plot the trajectory
//  pangolin::CreateWindowAndBind("Trace Viewer_" + name, 1024, 768);
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//  pangolin::OpenGlRenderState s_cam(
//      pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
//      pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));
//
//  pangolin::View &d_cam = pangolin::CreateDisplay()
//                              .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175),
//                                         1.0, -1024.0f / 768.0f)
//                              .SetHandler(new pangolin::Handler3D(s_cam));
//
//  while (pangolin::ShouldQuit() == false) {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    d_cam.Activate(s_cam);
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    glLineWidth(2);
//    for (size_t i = 0; i < pi_g.size() - 1; i++) {
//      glColor3f(0.0f, 1, 0.0f); // 这里稍作改动 将真值设置为绿色
//      glBegin(GL_LINES);
//      auto p1 = pi_g[i], p2 = pi_g[i + 1], p3 = pi_e[i], p4 = pi_e[i + 1];
//      glVertex3d(p1[0], p1[1], p1[2]);
//      glVertex3d(p2[0], p2[1], p2[2]);
//      glColor3f(1, 0.0f, 0.0f); // 这里稍作改动 将估计值设置为红色
//      glVertex3d(p3[0], p3[1], p3[2]);
//      glVertex3d(p4[0], p4[1], p4[2]);
//      glEnd();
//    }
//    pangolin::FinishFrame();
//    usleep(5000); // sleep 5 ms
//  }
//  return true;
//}