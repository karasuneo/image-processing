//
//  hist.cpp
//  03_01_negaposi_k21116
//
//  Created by k21116kk on 2022/05/11.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/kagoshima.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    
    int x, y;//アクセス用の変数
    
    //変換前の画素値の最小値、最大値、変換後の画素値の最小値、最大値
    unsigned char Imin, Imax, Dmin, Dmax;
    
    //初期値の入力
    Imax = 0;
    Imin = 255;
    
    //変換後の画素値の入力
    Dmin = 0;
    Dmax = 255;
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //出力画像のメモリ確保(グレスケ化してから)
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    
    //画像の操作
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            
            //画素値(s)取得　二重配列だから(x, y)ではなく(y, x)になっている
            unsigned char s = src_img.at<unsigned char>(y, x);
            
            //最小値取得
            if (Imin > s) {
                Imin = s;
            }
            
            //最大値取得
            if (Imax < s) {
                Imax = s;
            }
        }
    }
    
    fprintf(stderr, "Imin = %d, Imax = %d\n", Imin, Imax);
    
    //線形変換
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s =src_img.at<unsigned char>(y, x);
            
            //コントラストの演算
            s = ((Dmax-Dmin) / (Imax-Imin)) * ((s - Imin) + Dmin);
            
            dst_img.at<unsigned char>(y, x) = s;
        }
    }

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
