//
//  gaussian.cpp
//  avv_filter
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //出力画像のメモリ確保
    cv::Mat tmp_img;
    cv::Mat dst_img;
    
    //ソーベルフィルタ
    cv::Sobel(src_img, tmp_img, CV_32F, 1, 0);
    
    //適切な画像を表示できる様変換
    cv::convertScaleAbs(tmp_img, dst_img);
    

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}

