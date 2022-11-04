//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.


#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル名
#define FILE_NAME "gem1.jpg"

//ウィンドウ名
#define INPUT_WINDOW "input"
#define MAG_WINDOW "Magnitude"
#define RESULT_WINDOW "Result"

#define TH (20)
#define MAX_VAL (255)
#define HUE_MIN (20.0) // Hの最小値
#define HUE_MAX (60.0) // Hの最大値
#define SAT_MIN (100.0) // Sの最小値
#define SAT_MAX (200.0) // Sの最大値


int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, hsv_img, tmp_img, dst_img, b;
    
    cv::Vec3b p; //色値

    //カラー画像(省略可能)
    //1. エッジ検出
    //1. 入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    

    
    // 2. 出力二値画像の領域を確保(初期値ゼロ:黒)
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    // 3. 色変換 (BGR → HSV)
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    for (int y=0; y<hsv_img.rows; y++) {
        for (int x=0; x<hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); // 各画素のHSV値を取得
            // HSV色空間で色を検出
            if (p[0] >= HUE_MIN && p[0] <=HUE_MAX && p[1] >= SAT_MIN && p[1] <=SAT_MAX) {
                dst_img.at<uchar>(y,x) = MAX_VAL; // しきい値条件が適合したら白画素
            }
        }
    }

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
