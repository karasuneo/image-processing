//
//  hist.cpp
//  03_01_negaposi_k21116
//
//  Created by k21116kk on 2022/05/11.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../Debug/red_rectangle.jpg"

int main(int argc, const char* arg[]){
    
    int i, x, y;//アクセス用の変数
    
    int hist[COLOR_MAX];
    
    
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //ヒストグラム用配列の初期化
    for (int i=0; i<COLOR_MAX; i++) {
        hist[i] = 0;
    }
    
    //ヒストグラムの生成
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            
            hist[(int)s]++;//画素数の計算
            
        }
    }
    
    //出力(Number or Excel用に印字)
    for (i=0; i<COLOR_MAX; i++) {
        printf("%d %d\n", i, hist[i]);
    }
}
