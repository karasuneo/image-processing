//
//  final3_src_k21116.cpp
//  final3_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//



#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "input1.jpg"

#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    //入力画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //出力画像のメモリ確保
    cv::Mat tmp_img, dst_img;
    
    //ソーベルフィルタ
    cv::Sobel(src_img, tmp_img, CV_32F, 1, 0);
    
    //適切な画像を表示できる様変換
    cv::convertScaleAbs(tmp_img, dst_img);
    
    //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    
    cv::waitKey();
    
    return 0;
}
