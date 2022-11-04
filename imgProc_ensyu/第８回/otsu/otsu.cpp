//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/red_rectangle.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_GRAY "output_gray"
#define WINDOW_NAME_OUTPUT "output"
#define TH (127)
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
    cv::Mat dst_img = cv::Mat(gray_img.size(), CV_8UC1);
   
    //cv::THRESH_BINARY:閾値以上をmax_valueに
    //cv::THRESH_BINARY_INV:閾値以下をmax_valueに
    //cv::THRESH_BINARY_INVはR,G,B一つずつに[0][255]の二値化をやっている
    cv::threshold(gray_img, dst_img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_GRAY, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
