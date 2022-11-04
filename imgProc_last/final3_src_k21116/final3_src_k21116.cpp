//
//  final3_src_k21116.cpp
//  final3_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//


#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "input1.jpg"

#define WINDOW_NAME_OUTPUT "output"

//クロージング・オープニングの回数
#define COUNT (3)

//二値化の閾値
#define TH (90)
#define TH_R (150)
#define TH_G (120)
#define TH_B (120)

//白画素、黒画素の値
#define MAX_VAL (255)
#define MIN_VAL (0)

//面積の閾値
#define TH_AREA (3000)

int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;
    
    //入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    
    //入力失敗の場合
    if (src_img.empty()) {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    //二値画像の領域を確保(初期値ゼロ:黒)
    bin_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
   
    //グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //画素の走査
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            cv::Vec3b s_src = src_img.at<cv::Vec3b>(y, x);
            unsigned char s_gray = gray_img.at<uchar>(y, x);
            
            if ((s_src[0] <= TH_B && s_src[1] <= TH_G && s_src[2] >= TH_R) || s_gray <= TH) {
                //閾値条件が適合したら白画素
                bin_img.at<uchar>(y,x) = MAX_VAL;
            }else {
                //閾値条件が適合したら黒画素
                bin_img.at<uchar>(y,x) = MIN_VAL;
            }
        }
    }
    
    //クロージング・オープニング
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //配列の定義
    std::vector< std::vector< cv::Point > > contours;
    
    //画像をコピー
    tmp_img = bin_img.clone();
    dst_img = src_img.clone();
    
    //外輪郭のみ
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    //外接長方形を描画
    for (int i=0; i<contours.size(); i++) {
        double S = cv::contourArea(contours[i]);
        if (S > TH_AREA) {
            cv::Rect bb;
            bb = cv::boundingRect(contours[i]);
            cv::rectangle(dst_img, bb, CV_RGB(0, 0, 0), 2);
        }
    }
    
    //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
