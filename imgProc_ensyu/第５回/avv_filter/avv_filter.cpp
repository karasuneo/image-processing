//
//  filter2D.cpp
//  
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_THREE "output_th"
#define WINDOW_NAME_OUTPUT_FIVE "output_fi"

#define FILTER_SIZE (5)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    cv::Mat dst_th_img;
    cv::Mat dst_fi_img;
    
    double filter_th[] = {1.0/9.0, 1.0/9.0, 1.0/9.0,
                         1.0/9.0, 1.0/9.0, 1.0/9.0,
                         1.0/9.0, 1.0/9.0, 1.0/9.0};
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_th = cv::Mat(3, 3, CV_32F, filter_th);
    //正規化（やらないと画素値が255を超えるため）
    cv::normalize(kernel_th, kernel_th, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst_th_img, -1, kernel_th);
    
    double filter_fi[] = {1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
                          1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
                          1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
                          1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
                          1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,};
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_fi = cv::Mat(5, 5, CV_32F, filter_fi);
    //正規化（やらないと画素値が255を超えるため）
    cv::normalize(kernel_fi, kernel_fi, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst_fi_img, -1, kernel_fi);
    
    

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_THREE, dst_th_img);
    cv::imshow(WINDOW_NAME_OUTPUT_FIVE, dst_fi_img);
    cv::waitKey();
    
    return 0;
}
