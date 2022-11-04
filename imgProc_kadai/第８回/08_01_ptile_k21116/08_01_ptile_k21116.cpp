//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/ptile.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char* arg[]){
    int hist[COLOR_MAX];
    
    //imread:ファイルから画像をグレースケール化してから読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //配列の初期化
    for (int i=0; i<COLOR_MAX; i++) {
        hist[i] = 0;
    }
    
    //ヒストグラムの生成
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            hist[(int)s]++;//画素数の計算
        }
    }
    //輝度値比率4:1　
    double p = 4.0 / (4.0+1.0);
    double area_total = src_img.cols * src_img.rows * p;
    double area = 0;
    int th = 0;
    
    for (int i=0; i<COLOR_MAX; i++) {
        //全体面積の取得
        area += hist[i];//画素数の計算
        if (area > area_total ) {
            th = i;
            break;
        }
    }
    
    //メモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    
    printf("%lf\n", area);
    printf("%d\n", th);
    
    for (int i=0; i<COLOR_MAX; i++) {
        printf("%d %d\n", i, hist[i]);
    }
    
    cv::threshold(src_img, dst_img, th, 255, cv::THRESH_BINARY);
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
