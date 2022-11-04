//
//  01_01_face_x21116.cpp
//  
//
//  Created by k21116kk on 2022/04/13.
//

#include <iostream>
#include <cstdio>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/aquarium.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"


int main(int argc, const char * argv[]) {
    int x, y;
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        return (-1);
    }
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    int width[5];
    for (int i=0; i<5; i++) {
        width[i] = (src_img.cols/6) * (i+1);
    }
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            if (s[0] >= 100) {
                s[0] = 0;
                s[1] = 0;
                s[2] = 0;
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    return 0;
}

