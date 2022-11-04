//
//  hist.cpp
//  03_01_negaposi_k21116
//
//  Created by k21116kk on 2022/05/11.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../Debug/image2.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    //アクセス用の変数
    int i, x, y;
    
    //
    int hist[COLOR_MAX];
    
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //ヒストグラム用配列の初期化
    for (int i=0; i<COLOR_MAX; i++) {
        hist[i] = 0;
    }
    
    //出力画像のメモリ確保(グレスケ化してから)
    
    cv::Mat dst_img(src_img, cv::COLOR_BGR2GRAY);
    //線形変換
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s =src_img.at<unsigned char>(y, x);
            
            //輝度値の値に応じて二色化
            
            if ((int)s < 120) {
                s = 255;
                dst_img.at<uchar>(y, x) = s;
            }else{
                s = 0;
                dst_img.at<uchar>(y, x) = s;
            }
        }
    }
    
    for (y=0; y<dst_img.rows; y++) {
        for (x=0; x<dst_img.cols; x++) {
            //画素値の取得
            unsigned char s = dst_img.at<unsigned char>(y, x);
            
            hist[(int)s]++;//画素数の計算　画素値(0〜255)
        }
    }
    
    
    
    
    for (i=0; i<COLOR_MAX; i++) {
        printf("%d %d\n", i, hist[i]);//左:輝度値　右:その輝度値の画素数
    }
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
