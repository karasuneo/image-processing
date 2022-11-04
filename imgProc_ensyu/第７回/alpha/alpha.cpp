//
//  filter2D.cpp
//  
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "./input1.jpg"
#define FILE_NAME2 "./input2.jpg"
#define ALPHA (0.3)


#define WINDOW_NAME_INPUT1 "input1"
#define WINDOW_NAME_INPUT2 "input2"
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
    
    
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
    int x, y;
    
    for(y=0; y<src_img1.rows; y++){
        for(x=0; x<src_img1.cols; x++){
            double s1 = (double)src_img1.at<unsigned char>(y, x);
            double s2 = (double)src_img2.at<unsigned char>(y, x);
            
            int s_result = ALPHA * s1 +(1.0 - ALPHA) * s2;
            result_img.at<unsigned char>(y, x) = (unsigned char)s_result;
        }
    }
    
    //cv::imshow(WINDOW_NAME_INPUT1, src1_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    
    return 0;
}
