//
// Created by jian on 2021/4/20.
//

#include "zhang_config.h"


void GetParentPath(string &parentDIR)
{
    string strPath = "";
    char exeFullPath[MAX_FILE_PATH]; // Full path
    int i;
    int len = readlink("/proc/self/exe", exeFullPath, MAX_FILE_PATH - 1);
    if (len < 0 || (len >= MAX_FILE_PATH - 1))
    {
        return;
    }
    exeFullPath[len] = '\0';
    for (i = len; i >= 0; i--)
    {
        if (exeFullPath[i] == '/')
        {
            exeFullPath[i + 1] = '\0';
            break;
        }
    }
    strPath = exeFullPath;
    size_t pos = strPath.find("bin");
    parentDIR = strPath.substr(0, pos);
}


void SaveCalibrationResult(int img_num, cv::Size image_size, cv::Mat cameraMatrix, cv::Mat distCoeffs, vector<cv::Mat> rvecs, vector<cv::Mat> tvecs, vector<double> reproject_err)
{
    string parentDIR;
    GetParentPath(parentDIR);
    string result_txt = parentDIR + "test/" + "CalibrationResult.txt";
    ofstream fout(result_txt);
    fout << "------------------Calibration Result------------------" << endl;
    fout << "Number of all images: " << img_num << endl;
    fout << "Number of valid images: " << rvecs.size() << endl;
    fout << "Intrinsic cameraMatrix: " << endl << cameraMatrix << endl;
    fout << "Distortion coefficient: " << endl << distCoeffs << endl;
    fout << "Rotation vectors: " << endl;
    for(int i = 0; i < rvecs.size(); i++)
    {
        fout << i+1 << ": " << rvecs[i] << endl;
    }
    fout << "Translation vectors: " << endl;
    for(int i = 0; i < rvecs.size(); i++)
    {
        fout << i+1 << ": "<< tvecs[i] << endl;
    }
    fout << "Reprojection Error: " << endl;
    for(int i = 0; i < rvecs.size(); i++)
    {
        fout << i+1 << ": "<< reproject_err[i] << endl;
    }
    fout.close();
    cout << "Save calibration result at: " << endl << result_txt << endl;
}
