#include <iostream>

#include <eigen3/Eigen/Core>

#include <opencv2/core/core.hpp>
#include <opencv2/flann/flann.hpp>

int main() {
	int point_num = 100;
	cv::Mat points = cv::Mat::zeros(point_num, 1, CV_32FC2);
	for(int i=0 ; i<point_num ; ++i) {
		Eigen::Vector2f pt = Eigen::Vector2f::Random();
		points.at<cv::Vec2f>(0, i)[0] = pt.coeff(0);
		points.at<cv::Vec2f>(0, i)[1] = pt.coeff(1);
	}

	int cluster_num = 10;
	cv::Mat_<int> clusters(points.size(), CV_32SC1);
	cv::Mat centers;
	cv::kmeans(points, cluster_num, clusters, cvTermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER, 10, 1.0), 1, cv::KMEANS_PP_CENTERS, centers);
	std::cout << clusters << std::endl;
	return 0;
}
