#include <iostream>
#include <string>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "zhang_config.h"
#include "img_process.h"

using namespace std;

int main( int argc, char** argv )
{
    cout << "--------Configuring chessboard--------" << endl;
    if ( argc != 4 )
    {
        cout<<"   Error: please enter the correct parameters" << endl;
        cout<<"   exe_path, width of chessboard, height of chessboard, size of block" << endl;
        return 1;
    }
    int chess_width = atoi(argv[1]);
    int chess_height = atoi(argv[2]);
    int block_size = atoi(argv[3]);
    cv::Size pattern_size;
    pattern_size.width = chess_width - 1;
    pattern_size.height = chess_height - 1;
    cout << "   width of chessboard:  " << chess_width << endl;
    cout << "   height of chessboard: " << chess_height << endl;
    cout << "   size of block:        " << block_size << endl;


    cout << "--------Loading images--------" << endl;
    string parent_dir;
    GetParentPath(parent_dir);
    string img_dir = parent_dir + "img/";
    cv::String img_dir_pattern = img_dir + "*.jpg";
    vector<string> src_fullname;
    vector<cv::Mat> src_img = ReadImage(img_dir_pattern, src_fullname);
    cout << "   img_dir: " << img_dir << endl;
    cout << "   Loading " << src_img.size() << " images in totally." << endl;


    cout << "--------Extracting corners--------" << endl;
    vector<cv::Mat> gray_img = GetGrayImage(src_img);
    vector<cv::Mat> valid_img;
    vector<vector<cv::Point2f>> multi_image_corners = FindCorners(gray_img, valid_img,src_fullname, pattern_size);
    vector<vector<cv::Point3f>> multi_world_corners = GenerateWorldCorner(valid_img.size(), pattern_size, block_size);
    cout << "   Extracting " << multi_image_corners.size() << "*" << multi_image_corners[0].size() << " corners in totally." << endl;


    cout << "--------Calculating HomogeneousMatrix--------" << endl;


/*
    cout << "--------Calibrating by OpenCV method--------" << endl;
    cv::Size image_size = valid_img[0].size();
    //cout << image_size.width << "," << image_size.height << endl;
    cv::Mat cameraMatrix, distCoeffs;
    vector<cv::Mat> rvecs, tvecs, rvecs2, tvecs2;
    double reprojection_error                                             // @return: sum of reprojection errors
            = cv::calibrateCamera(multi_world_corners,                    //InputArrayOfArrays objectPoints: corners in world coordinate, vector<vector<cv::Point3f>>
                                  multi_image_corners,                    //InputArrayOfArrays imagePoints: corners in pixel coordinate, vector<vector<cv::Point2f>>
                                  image_size,                             //Size imageSize: size of image, cv::Size
                                  cameraMatrix,                           //InputOutputArray cameraMatrix: Input intrinsic cameraMatrix, cv::Mat
                                  distCoeffs,                             //InputOutputArray distCoeffs: Input distortion coefficient, cv::Mat
                                  rvecs,                                  //OutputArrayOfArrays rvecs: rotation vector, vector<cv::Mat>
                                  tvecs,                                  //OutputArrayOfArrays tvecs, translation vectors, vector<cv::Mat>
                                  CV_CALIB_FIX_K5                         //int flags = 0: select computational model
                                                                            //TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, DBL_EPSILON);
    );

    //cout << "->>>>Calibration Result" << endl;
    //cout << "cameraMatrix: " << cameraMatrix << endl;
    //cout << "distCoeffs: " << distCoeffs << endl;
    //cout << "reprojection_error: " << reprojection_error << endl;
    //cout << "rvecs[0]: " << rvecs[0] << endl;
    //cout << "tvecs[0]: " << tvecs[0] << endl;
    //cout << "->>>>Reprojection Result" << endl;
    vector<double> re_reprojection_error;
    for(int i = 0; i < valid_img.size(); i++)
    {
        double err = 0.0;
        vector<cv::Point2f> re_image_corners;   //reproject points in pixel coordinate
        vector<cv::Point2f> temp_image_corners = multi_image_corners[i];
        cv::projectPoints( multi_world_corners[i],           //InputArray objectPoints,
                           rvecs[i],                         //InputArray rvec,
                           tvecs[i],                         //InputArray tvec,
                           cameraMatrix,                     //InputArray cameraMatrix,
                           distCoeffs,                       //InputArray distCoeffs,
                           re_image_corners                  //OutputArray imagePoints,
                                                             //OutputArray jacobian=noArray(),
                                                             //double aspectRatio=0 );
        );
        cv::Mat temp_image_cornersMat = cv::Mat(1,temp_image_corners.size(),CV_32FC2);
        cv::Mat re_image_cornersMat = cv::Mat(1,re_image_corners.size(), CV_32FC2);
        for (int j = 0 ; j < temp_image_corners.size(); j++)
        {
            re_image_cornersMat.at<cv::Vec2f>(0,j) = cv::Vec2f(re_image_corners[j].x, re_image_corners[j].y);
            temp_image_cornersMat.at<cv::Vec2f>(0,j) = cv::Vec2f(temp_image_corners[j].x, temp_image_corners[j].y);
        }
        err = norm(re_image_cornersMat, temp_image_cornersMat, cv::NORM_L2);
        re_reprojection_error.push_back(err);
        //cout << i+1 << ": " << err << endl;
    }
    SaveCalibrationResult(src_img.size(), image_size, cameraMatrix, distCoeffs, rvecs, tvecs, re_reprojection_error);
*/


    return 0;
}
