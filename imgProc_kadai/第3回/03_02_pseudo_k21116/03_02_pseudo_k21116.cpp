//
//  03_02_pseudo_k21116.cpp
//  
//
//  Created by k21116kk on 2022/04/27.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/dot_gray_rectangle.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256) //色値


int main(int argc, const char * argv[]) {
    //画像の入力 (グレースケール入力)
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty()) { //入力失敗の場
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    //出力画像のメモリ確保 (グレースケール)
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    
    
    uchar lut_src[COLOR_NUM]; //入力画像のピクセルの輝度値
    cv::Vec3b lut_dst[COLOR_NUM]; //出力画像のピクセルの輝度値(RGB)
    for (int i=0; i<COLOR_NUM; i++) {
        if (i <= 63) {
            lut_dst[i][0] = 255;
            lut_dst[i][1] = i*4;
            lut_dst[i][2] = 0;
        }else if (64 <= i && i <= 127) {
            lut_dst[i][0] = 255-(i*4);
            lut_dst[i][1] = 255;
            lut_dst[i][2] = 0;
        }else if (128 <= i && i <= 191) {
            lut_dst[i][0] = 0;
            lut_dst[i][1] = 255;
            lut_dst[i][2] = i*4;
        }else{
            lut_dst[i][0] = 0;
            lut_dst[i][1] = 255-(i*4);
            lut_dst[i][2] = 255;
        }
    }
    //画像の走査
    for (int y=0; y<dst_img.rows; y++) {
        for (int x=0; x<dst_img.cols; x++) {
            uchar s = src_img.at<uchar>(y, x);
            dst_img.at<cv::Vec3b>(y, x) = lut_dst[s];
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

