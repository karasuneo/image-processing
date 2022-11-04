//
//  03_01_negaposi_k21116.cpp
//  
//
//  Created by k21116kk on 2022/04/27.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256) //色値

int main(int argc, const char * argv[]) {
    
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    cv::Mat gray_img;//gray_imageの定義
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);//src_imgをグレースケール化してgray_imgに代入
    cv::Mat dst_img = cv::Mat(gray_img.size(), CV_8UC1);//1個のCV_8U(符号なしの8ビット整数)モノクロ画像の初期値、サイズをgray_imgと同じにしてdst_imgに代入
    uchar lut[COLOR_NUM];//輝度値の取得
    for (int i=0; i<COLOR_NUM; i++) {
        lut[i]  = 255 - i;//
    }
    
    for (int y=0; y<dst_img.rows; y++) {
        for (int x=0; x<dst_img.cols; x++) {
            uchar s = gray_img.at<uchar>(y, x); //画素値の取得
            dst_img.at<uchar>(y, x) = lut[s];
        }
    }
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey();
    return 0;
}

