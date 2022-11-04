//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.


#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル名
#define FILE_NAME "gem1.jpg"

//ウィンドウ名
#define INPUT_WINDOW "input"
#define MAG_WINDOW "Magnitude"
#define RESULT_WINDOW "Result"

#define COUNT (15)
#define TH (20)
#define MAX_VAL (255)
#define R_MIN (0) //Rの最小値
#define R_MAX (50) //Rの最大値
#define G_MIN (50) //Gの最小値
#define G_MAX (100) //Gの最大値
#define HUE_MIN (20.0) // Hの最小値
#define HUE_MAX (60.0) // Hの最大値
#define SAT_MIN (100.0) // Sの最小値
#define SAT_MAX (200.0) // Sの最大値


int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, hsv_img, bin_img, tmp_img, dst_img;
    cv::Mat black_img, green_img, golden_img;
    cv::Mat bin_black_img, bin_green_img, bin_golden_img;
    cv::Vec3b p;

    //入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    //グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //二値化
    cv::threshold(gray_img, bin_black_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);//黒曜石の抽出
    
    //クロージング・オープニング
    cv::dilate(bin_black_img, bin_black_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_black_img, bin_black_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_black_img, bin_black_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //5. 輪郭追跡による領域検出
    std::vector< std::vector< cv::Point > > contours;
    
    //二値画像をコピー
    tmp_img = bin_black_img.clone();
    
    //外輪郭のみ
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    
    
    //入力画像を出力画像にコピー
    dst_img = src_img.clone();
    
    //外接長方形を描画
    for (int i=0; i<contours.size(); i++) {
        cv::Rect bb;
        bb = cv::boundingRect(contours[i]);
        cv::rectangle(dst_img, bb, CV_RGB(255, 0, 0), 2);
    }
    
    //個数を出力
    std::cout << "Black gem = " << contours.size() << std::endl;
    
    //出力二値画像の領域を確保(初期値ゼロ:黒)
    bin_green_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
      //しきい値処理
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //各画素のBGR値を取得
            p = src_img.at<cv::Vec3b>(y, x);
            
            // RGB色空間で緑色を検出
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <=R_MAX) {
                // しきい値条件が適合したら白画素
                bin_green_img.at<uchar>(y,x) = MAX_VAL;
            }
        }
    }
    
    //クロージング・オープニング
    cv::dilate(bin_green_img, bin_green_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_green_img, bin_green_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_green_img, bin_green_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //配列の初期化
    contours.clear();
    
    //二値画像をコピー
    tmp_img = bin_green_img.clone();
    
    //外輪郭のみ
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
        //指定領域の塗りつぶし
        cv::drawContours(dst_img, contours, i, CV_RGB(0, 255, 0), -1);
    }
    
    //個数を出力
    std::cout << "Green gem = " << contours.size() << std::endl;
    
    //二値画像の領域を確保(初期値ゼロ:黒)
    bin_golden_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    // 3. 色変換 (BGR → HSV)
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    for (int y=0; y<hsv_img.rows; y++) {
        for (int x=0; x<hsv_img.cols; x++) {
            //各画素のHSV値を取得
            p = hsv_img.at<cv::Vec3b>(y, x);
            
            // HSV色空間で色を検出
            if (p[0] >= HUE_MIN && p[0] <=HUE_MAX && p[1] >= SAT_MIN && p[1] <=SAT_MAX) {
                //しきい値条件が適合したら白画素
                bin_golden_img.at<uchar>(y,x) = MAX_VAL;
            }
        }
    }
    
    //クロージング・オープニング
    cv::dilate(bin_golden_img, bin_golden_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_golden_img, bin_golden_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_golden_img, bin_golden_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //配列の初期化
    contours.clear();
    
    //二値画像をコピー
    tmp_img = bin_golden_img.clone();
    
    //外輪郭のみ
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    //外接円を描画
    for (int i=0; i<contours.size(); i++) {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contours[i], center, radius);
        
        //外接円を求める
        cv::circle(dst_img, center, (int)radius, CV_RGB(255, 255, 255), 2);
    }

    //個数を出力
    std::cout << "Golden gem = " << contours.size() << std::endl;

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
