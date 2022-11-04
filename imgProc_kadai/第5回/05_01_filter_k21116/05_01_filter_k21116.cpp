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
#define WINDOW_NAME_OUTPUT_THREE "output"


#define FILTER_SIZE (7)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    cv::Mat dst_img;
    
    double filter_h[FILTER_SIZE*FILTER_SIZE];
    for (int i=0; i<(FILTER_SIZE*FILTER_SIZE)-1; i++) {
        filter_h[i] = 1./(double)(FILTER_SIZE*FILTER_SIZE);
    }
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_h = cv::Mat(FILTER_SIZE, FILTER_SIZE, CV_32F, filter_h);
    //正規化（やらないと画素値が255を超えるため）
    cv::normalize(kernel_h, kernel_h, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst_img, -1, kernel_h);
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_THREE, dst_img);
    cv::waitKey();
    
    return 0;
}
