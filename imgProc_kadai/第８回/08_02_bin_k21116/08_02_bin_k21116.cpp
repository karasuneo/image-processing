//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/red_green_rectangle.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_GRAY "output_gray"
#define WINDOW_NAME_OUTPUT_RED "output_red"
#define WINDOW_NAME_OUTPUT_GREEN "output_green"
#define TH_RED (159)
#define TH_GREEN (159)
#define HIGHVAL (255)
#define LOWVAL (0)
#define COLOR_MAX (256)

int main(int argc, const char* arg[]){
    int hist_red[COLOR_MAX];
    int hist_green[COLOR_MAX];
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    for (int i=0; i<COLOR_MAX; i++) {
        hist_red[i] = 0;
        hist_green[i] = 0;
    }
    
    //s[1]のヒストグラムの生成
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<cv::Vec3b>(y, x)[1];
            hist_green[(int)s]++;//画素数の計算
        }
    }
    
    //s[2]のヒストグラムの生成
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<cv::Vec3b>(y, x)[2];
            hist_red[(int)s]++;//画素数の計算
        }
    }
    
    cv::Mat gray_img;
    //画像をグレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //メモリ確保
    cv::Mat bin_red_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat bin_green_img = cv::Mat(src_img.size(), CV_8UC1);
    
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            double s1 = gray_img.at<unsigned char>(y, x);
            if (s[2] > TH_RED) {
                bin_red_img.at<uchar>(y, x) = 255;
            }else{
                bin_red_img.at<uchar>(y, x) = 0;
            }
            if (s[1] > TH_GREEN) {
                bin_green_img.at<uchar>(y, x) = 255;
            }else{
                bin_green_img.at<uchar>(y, x) = 0;
            }
            //bin_red_img.at<unsigned char>(y, x) = s1;
        }
    }
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_GRAY, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT_RED, bin_red_img);
    cv::imshow(WINDOW_NAME_OUTPUT_GREEN, bin_green_img);
    cv::waitKey();
    
    return 0;
}
