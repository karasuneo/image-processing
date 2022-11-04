//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/red_rectangle.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_INPUT_GRAY "input_gray"
#define WINDOW_NAME_OUTPUT "output"
#define TH (100)
#define HIGHVAL (255)
#define LOWVAL (0)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    cv::Mat gray_img;
    
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::Mat bin_img = cv::Mat(gray_img.size(), CV_8UC1);
    //出力画像のメモリ確保(グレスケ化してから)
    cv::Mat dst_img;

    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            if (gray_img.at<uchar>(y, x) < TH) {
                bin_img.at<uchar>(y, x) = HIGHVAL;
            }else{
                bin_img.at<uchar>(y, x) = LOWVAL;
            }
        }
    }
    
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_INPUT_GRAY, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT, bin_img);
    cv::waitKey();
    
    return 0;
}
