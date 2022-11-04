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

#define COUNT (15)
#define TH (20)
#define MAX_VAL (255)
#define HUE_MIN (20.0) // Hの最小値
#define HUE_MAX (60.0) // Hの最大値
#define SAT_MIN (100.0) // Sの最小値
#define SAT_MAX (200.0) // Sの最大値


int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, hsv_img, bin_img, tmp_img, dst_img;
    
    cv::Vec3b p; //色値

    //カラー画像(省略可能)
    //1. エッジ検出
    //1. 入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //3. 二値化
    cv::threshold(gray_img, bin_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);

    //4. クロージング・オープニング
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //5. 輪郭追跡による領域検出
    std::vector< std::vector< cv::Point > > contours;
    tmp_img = bin_img.clone(); //二値画像をコピー
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); // 外輪郭のみ
    //6. 外接円を描画
    dst_img = src_img.clone(); //入力画像を出力画像にコピー
    for (int i=0; i<contours.size(); i++) {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contours[i], center, radius);
        //外接円を求める
        cv::circle(dst_img, center, (int)radius, CV_RGB(255, 0, 0), 2); // 赤色
    }
    
    //7. 個数を出力
    std::cout << "Black gem = " << contours.size() << std::endl;

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
