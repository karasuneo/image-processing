//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "a_img.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_GRAY "output_gray"
#define WINDOW_NAME_OUTPUT_BIN "output_bin"
#define WINDOW_NAME_OUTPUT_EX "output_ex"
#define WINDOW_NAME_OUTPUT_SH "output_sh"
#define TH (100)
#define HIGHVAL (255)
#define LOWVAL (0)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    cv::Mat gray_img;
    //画像をグレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //メモリ確保
    cv::Mat bin_img = cv::Mat(gray_img.size(), CV_8UC1);
   
    //cv::THRESH_BINARY:閾値以上をmax_valueに
    //cv::THRESH_BINARY_INV:閾値以下をmax_valueに
    //cv::THRESH_BINARY二値化をやっている
    cv::threshold(gray_img, bin_img, TH, 255, cv::THRESH_BINARY);
    
    
    //メモリ確保
    cv::Mat dst_ex_img = cv::Mat(gray_img.size(), CV_8UC1);
    cv::Mat dst_sh_img = cv::Mat(gray_img.size(), CV_8UC1);
    
    //膨張
    for (int i=0; i<10; i++) {
        //膨張
        cv::dilate(bin_img, dst_ex_img, cv::Mat(), cv::Point(-1, -1), i);
        cv::imshow(WINDOW_NAME_OUTPUT_EX, dst_ex_img);
    }
    
    //収縮
    for (int i=0; i<10; i++) {
        //収縮
        cv::erode(dst_ex_img, dst_sh_img, cv::Mat(), cv::Point(-1, -1), i);
        cv::imshow(WINDOW_NAME_OUTPUT_SH, dst_sh_img);
    }
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_GRAY, gray_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_BIN, bin_img);
    cv::waitKey();
    
    return 0;
}
