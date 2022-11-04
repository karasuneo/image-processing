//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.
//

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




int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, dst_img;
    

    //カラー画像(省略可能)
    
    //1. 入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //3. 二値化
    cv::threshold(gray_img, dst_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
