//
//  changeColor.cpp
//
//
//  Created by Masashi Morimoto on 2022/06/22.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "fruit_image.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

// 0. 定数の定義
#define HUE_MIN (20) // Hの最小値
#define HUE_MAX (35) // Hの最大値（シフト幅）
#define SAT_TH (200) // Sの閾値
#define VAL_TH (225) // Vの閾値

//二値化閾値
#define BIN_TH (100)


int main(int argc, const char * argv[]) {
    // 1. 変数の宣言
    int x, y;    //走査用
    cv::Vec3b p; //色値(HSV)
    int h,s,v;   //色値(各要素)
    cv::Mat src_img, gray_img, tmp_img, hsv_img, bin_img, dst_img;
    
    //輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;

    // 2. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    
    // 3. 色変換 (BGR → HSV)
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV_FULL);
    
    // 4. 出力二値画像の領域を確保（初期値ゼロ：黒）
    bin_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    dst_img = src_img.clone();
    

    // 5. 画像処理
    for (y=0; y<hsv_img.rows; y++) {
        for (x=0; x<hsv_img.cols; x++) {
            
            p = hsv_img.at<cv::Vec3b>(y, x);
            h = p[0]; s = p[1]; v = p[2];
            
            if (h >= HUE_MIN &&h <= HUE_MAX &&s >= SAT_TH && v >= VAL_TH){
                bin_img.at<uchar>(y, x) = 255;
            }else{
                bin_img.at<uchar>(y, x) = 0;
            }
        }
    }
    
    //6. 二値画像コピー
    tmp_img = bin_img.clone();
    
    cv::threshold(tmp_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    //7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
        double S;
        S = cv::contourArea(contours[i]);
        
        if (S >= 100) {
            cv::drawContours(dst_img, contours, i, CV_RGB(255, 255, 0), -1);
        }
    }

    // 8. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img); // 入力画像の表示
    cv::imshow(WINDOW_NAME_BINARY , bin_img); // 入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey(); // キー入力待ち (止める)
    return 0;
}

