//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "input1.jpg"
#define FILE_NAME2 "input2.jpg"
#define THERESHOLD (20)//閾値


#define WINDOW_NAME_INPUT1 "input1"
#define WINDOW_NAME_INPUT2 "input2"
#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    
    //画像が開けない時
    if (src_img1.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    if (src_img2.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    cv::Mat sub_img = cv::Mat(src_img1.size(), CV_8UC1);
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
    
    
    int x, y;
    
    for(y=0; y<src_img1.rows; y++){
        for(x=0; x<src_img1.cols; x++){
            int s1 = (int)src_img1.at<unsigned char>(y, x);
            int s2 = (int)src_img2.at<unsigned char>(y, x);
            
            int s_result = abs(s1 - s2);
            sub_img.at<unsigned char>(y, x) = s_result;
            
            if (s_result > THERESHOLD) {
                s_result = 255;
            }else{
                s_result = 0;
            }
            result_img.at<unsigned char>(y, x) = s_result;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT1, src_img1);
    cv::imshow(WINDOW_NAME_INPUT2, src_img2);
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    
    return 0;
    
    
}
