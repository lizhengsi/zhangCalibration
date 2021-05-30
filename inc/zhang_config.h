//
// Created by jian on 2021/4/20.
//

#ifndef ZHANGCALIBRATION_CONFIG_H
#define ZHANGCALIBRATION_CONFIG_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>


using namespace std;

#define MAX_FILE_PATH 100


/**
 * get the root directory of the project
 * @param parentDIR(in&out): the root directory of the project
 */
void GetParentPath(string &parentDIR);


/**
 * save .txt files of calibration result by OpenCV method
 * @param img_num: amount of valid images
 * @param image_size: size of every image(width, height)
 * @param cameraMatrix: intrinsic cameraMatrix
 * @param distCoeffs: distortion coefficient
 * @param rvecs: rotation vectors for every image
 * @param tvecs: translation vectors for every image
 * @param reproject_err: reproject errors for every image
 */
void SaveCalibrationResult(int img_num, cv::Size image_size, cv::Mat cameraMatrix, cv::Mat distCoeffs, vector<cv::Mat> rvecs, vector<cv::Mat> tvecs, vector<double> reproject_err);

#endif //ZHANGCALIBRATION_CONFIG_H
