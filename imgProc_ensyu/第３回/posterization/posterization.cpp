//
//  grayImg.cpp
//  
//
//  Created by k21116kk on 2022/04/27.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/apple_tree.jpg"

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
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    
    uchar lut[COLOR_NUM]; //ルックアップテーブル
    //ルックアップテーブルの生成 (4段階)4色で分けてる
    for (int i=0; i<COLOR_NUM; i++) {
        if (i <= 64) {
            lut[i] = 32;
        }else if (64 < i && i < 128) {
            lut[i] = 85;
        }else if (128 <= i && i <= 255) {
            lut[i] = 170;
        }else{
            lut[i] = 255;
        }
    }
    //画像の走査
    for (int y=0; y<dst_img.rows; y++) {
        for (int x=0; x<dst_img.cols; x++) {
            uchar s = src_img.at<uchar>(y, x); //画素値の取得
            //ルックアップテーブルによるポスタリゼーション
            dst_img.at<uchar>(y, x) = lut[s];
            
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

