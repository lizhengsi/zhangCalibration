//
// Created by jian on 2021/4/20.
//

#ifndef ZHANGCALIBRATION_CALCULATION_H
#define ZHANGCALIBRATION_CALCULATION_H

#include <string>
#include <vector>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

/**
 *
 * @param uv
 * @param uv1
 * @param xy1
 * @param M_alluv1
 * @param M_allxy1
 * @param image_count
 * @param board_size
 */
void InitHomogeneousMatrix(vector<vector<cv::Point2f>>& uv_corners, vector<vector<cv::Point3f> >& uv_corners_h,
                           vector<vector<cv::Point3f>>& xy1, vector<vector<cv::Mat> >& M_alluv1,
                           vector<vector<cv::Mat> >& M_allxy1, int& image_count, cv::Size& board_size);


void SolveHomogeneousMatrix(vector<vector<cv::Point3f> >& uv1, vector<vector<cv::Point3f> >& xy1,
                            vector<cv::Mat>& H, int& image_count, cv::Size& board_size);


void SolveIntrinsicMatrix(cv::Mat& B, cv::Mat& cameraMatrix,float& scale);


void OptimizeIntrinsicMatrix(cv::Mat& B, cv::Mat& cameraMatrix,float& scale);


void SolveExtrinsicVectors(vector<cv::Mat>& tvecsMat, vector<cv::Mat>& rvecsMat, cv::Mat& cameraMatrix, vector<cv::Mat>& H,
                    float& scale, vector<cv::Mat>& R_r, vector<cv::Mat>& Jett, vector<cv::Mat>& tvecsMat1,
                    vector<cv::Mat>& outcan,int& image_count);

void SolveDistCoeffs();


void OptimizeAllParameters();


#endif //ZHANGCALIBRATION_CALCULATION_H