//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.

//RGB空間使ってる

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
#define R_MIN (0) //Rの最小値
#define R_MAX (50) //Rの最大値
#define G_MIN (50) //Gの最小値
#define G_MAX (100) //Gの最大値


int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, dst_img;
    
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
    //4. カラー画像処理
    //入力画像と同じサイズ
    //1チャンネル、初期値0
      // 3. しきい値処理
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //カラー画像の画素はVec3b
            p = src_img.at<cv::Vec3b>(y, x); //各画素のBGR値を取得
            // RGB色空間で緑色を検出
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <=R_MAX) {
                dst_img.at<uchar>(y,x) = MAX_VAL; // しきい値条件が適合したら白画素
            }
        }
    //出力画像の画素はuchar
    }

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
