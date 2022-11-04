//
//  labeling.cpp
//
//
//  Created by b21702bb on 2021/06/22.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "challenge.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

//二値化閾値
#define BIN_TH (188)


int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    //色値の設定
    cv::Scalar color[] = {CV_RGB(255, 0, 0),
                          CV_RGB(255, 0, 255)
        
    };
    
    //2. 輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    
    //3. 画像の入力 (カラーで入力)
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を結果画像にコピー
    dst_img = src_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_img, gray_img,cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定閾値で実装．閾値: 100)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    //二値画像コピー
    tmp_img = bin_img.clone();
    
    //7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    
    //8. 輪郭の描画
    int count = 0;
    for (int i=0; i<contours.size(); i++) {
        double L, S, R;
        L = cv::arcLength(contours[i], true);
        S = cv::contourArea(contours[i]);
        R = (4*M_PI*S) / (L*L);
        
        if (S >= 50) {
            cv::drawContours(dst_img, contours, i, CV_RGB(255, 255, 255), -1);
            count++;
        }else {
            cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), -1);
        }
    }
    
    
    for (int y=0; y<bin_img.rows; y++) {
        for (int x=0; x<bin_img.cols; x++) {
            //画素値の取得
            cv::Vec3b s_dst = dst_img.at<cv::Vec3b>(y, x);
            
            if (s_dst[0] != 255 && s_dst[1] != 255 && s_dst[2] != 255) {
                s_dst[0] = 0;
                s_dst[1] = 0;
                s_dst[2] = 0;
            }
            
            dst_img.at<cv::Vec3b>(y, x) = s_dst;
            
        }
    }
    printf("%d", count);
    
    /*for (int y=0; y<bin_img.rows; y++) {
        for (int x=0; x<bin_img.cols; x++) {
            //画素値の取得
            double s_bin = bin_img.at<unsigned char>(y, x);
            cv::Vec3b s_dst = dst_img.at<cv::Vec3b>(y, x);
            
            if (s_dst[0] != 255) {
                s_dst[0] = 0;
                s_dst[1] = 0;
                s_dst[2] = 0;
            }
            
            dst_img.at<cv::Vec3b>(y, x) = s_dst;
            
        }
    }*/
    
    
    //9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    
    return 0;
}
