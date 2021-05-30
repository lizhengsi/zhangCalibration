//
// Created by jian on 2021/4/20.
//

#include "img_process.h"


vector<cv::Mat> ReadImage(cv::String pattern, vector<string> &img_name)
{
    vector<cv::String> fn;
    cv::glob(pattern, fn, false);
    vector<cv::Mat> images;
    size_t count = fn.size(); //number of png files in images folder
    for (size_t i = 0; i < count; i++)
    {
        if(cv::imread(fn[i]).empty())
        {
            cout << "   Error: Loading image failures!" << endl;
        }
        images.push_back(cv::imread(fn[i]));
        img_name.push_back(fn[i]);
//        cout << "   load image: " << img_name[i] << endl;
//        imshow("img_" + to_string(i), cv::imread(fn[i]));
//        cv::waitKey(200);
//        cv::destroyAllWindows();
    }
    return images;
}

vector<cv::Mat> GetGrayImage(const vector<cv::Mat> &src_img)
{
    vector<cv::Mat> images(src_img.size());
    for(int i = 0; i < src_img.size(); i++)
    {
        if(src_img[i].channels() == 1)
        {
            images[i] = src_img[i].clone();
            cout << src_img[i].type() << endl;
            break;
        }
        else
        {
            cvtColor( src_img[i], images[i], CV_BGR2GRAY );
//            imshow("gray_img_" + to_string(i), images[i]);
//            cv::waitKey(200);
//            cv::destroyAllWindows();
        }
    }
    return images;
}

/**
 * use functions of opencv to find pixel coordinates of corners in images, and remove invalid images manually
 * @param img(in): gray image
 * @param src_name(in): fullpath of src images
 * @param pattern_size(in): the amount of corners of chessboard(width, height)
 * @return: the sub-pixel coordinates of corners of all images
 */
vector<vector<cv::Point2f>> FindCorners(const vector<cv::Mat> &img, vector<cv::Mat> &valid_img, const vector<string> &src_name, const cv::Size &pattern_size)
{
    vector<cv::Point2f> corners;
    vector<vector<cv::Point2f>> img_corners;
    int invalid_num = 0;
    for(int i = 0; i < img.size(); i++)
    {
        //find corners in image, the amount of corner is according to pattern_size
        //if not enough corners, then return false
        bool found = cv::findChessboardCorners(img[i], pattern_size, corners,cv::CALIB_CB_ADAPTIVE_THRESH);
        if (!found) {
            cout << "   Error: find corners failed: " << src_name[i] << endl;
            break;
        }
        // get sub-pixel coordinates of the corners in the way of QuadCorner, improve the precision
        cv::find4QuadCornerSubpix(img[i], corners, cv::Size(5, 5));
        //cv::cornerSubPix(img[i], corners, cv::Size(11, 11), cv::Size(-1, -1),  cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.01));
        cv::drawChessboardCorners(img[i], pattern_size, corners, found);
        img_corners.push_back(corners);
        valid_img.push_back(img[i]);
//        for (auto val : corners) cout << val << endl;
//        cv::namedWindow("Chessboard_Corners_" + to_string(i));
//        cv::imshow("Chessboard_Corners_" + to_string(i), img[i]);
//        cv::waitKey(0);
//        cv::destroyAllWindows();
    }
    return img_corners;
}

/**
 * generate world coordinates of corners in chessboard
 * @param image_num(in): amount of valid images
 * @param pattern_size(in): the amount of corners of chessboard(width, height)
 * @param block_size(in): the block_size of chessboard(width, height)
 * @return: world coordinates of corners in chessboard for all valid images
 */
vector<vector<cv::Point3f>> GenerateWorldCorner(int image_num, const cv::Size &pattern_size, const int &block_size)
{
    int xCols = pattern_size.width;
    int yRows = pattern_size.height;
    vector<vector<cv::Point3f>> multi_world_corners;
    vector<cv::Point3f> world_corners;
    cv::Point3f point;
    for(int i = 0; i < yRows; i++)
    {
        for(int j = 0; j < xCols; j++)
        {
            point.x = (float)j * block_size;
            point.y = (float)i * block_size;
            point.z = 0.0;
            world_corners.push_back(point);
            //cout << i*xCols+j << ":" << world_corners[i*xCols+j] << endl;
        }
    }
    for(int i = 0; i < image_num; i++)
    {
        multi_world_corners.push_back(world_corners);
        //cout << i << ":" << multi_world_corners[i] << endl;
    }
    //cout << multi_world_corners[2][15] << endl;
    return multi_world_corners;
}