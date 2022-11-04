//
//  pixelAccess.cpp
//  
//
//  Created by k21116kk on 2022/04/20.
//

#include <iostream>
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
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            if (x < 10 || src_img.cols-10 <= x || y < 10 || src_img.rows-10 <= y) {
                s[0] = 255;
                s[1] = 255;
                s[2] = 255;
            }else {
                s[0] = s[0];
                s[1] = s[1];
                s[2] = s[2];
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    return 0;
}

