//
//  grayImg.cpp
//  
//
//  Created by k21116kk on 2022/04/27.
//

#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/apple_tree.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    //cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
    /*for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);//画像の画素へのアクセス
            uchar val = 0.114 * s[0]
            + 0.587 * s[1]
            + 0.299 *s[2];
            gray_img.at<uchar>(y, x) = val;
        }
    }*/
    
    //出力画像の変数宣言
    cv::Mat dst_img;
    //グレースケール化
    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);//
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    //cv::imshow(WINDOW_NAME_OUTPUT, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey();
    return 0;
}

