//
// Created by jian on 2021/4/20.
//

#ifndef ZHANGCALIBRATION_IMG_PROCESS_H
#define ZHANGCALIBRATION_IMG_PROCESS_H

#include <string>
#include <vector>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

/**
 * load all images in a dir
 * @param pattern(in): path pattern of images
 * @param img_name(in&out): full path of every image
 * @return: save all src images in a vector
 */
vector<cv::Mat> ReadImage(cv::String pattern, vector<string> &img_name);

/**
 * get gray image of the src image, prepare for finding corners
 * @param src_img(in): src images
 * @return: gray image of the src image
 */
vector<cv::Mat> GetGrayImage(const vector<cv::Mat> &src_img);

/**
 * use functions of opencv to find pixel coordinates of corners in images, and remove invalid images manually
 * @param img(in): gray image
 * @param src_name(in): fullpath of src images
 * @param pattern_size(in): the amount of corners of chessboard(width, height)
 * @return: the sub-pixel coordinates of corners of all images
 */
vector<vector<cv::Point2f>> FindCorners(const vector<cv::Mat> &img, vector<cv::Mat> &valid_img, const vector<string> &src_name, const cv::Size &pattern_size);

/**
 * generate world coordinates of corners in chessboard
 * @param image_num(in): amount of valid images
 * @param pattern_size(in): the amount of corners of chessboard(width, height)
 * @param block_size(in): the block_size of chessboard(width, height)
 * @return: world coordinates of corners in chessboard for all valid images
 */
vector<vector<cv::Point3f>> GenerateWorldCorner(int image_num, const cv::Size &pattern_size, const int &block_size);

#endif //ZHANGCALIBRATION_IMG_PROCESS_H