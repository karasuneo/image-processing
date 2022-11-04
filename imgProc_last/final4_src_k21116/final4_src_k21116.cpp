//
//  final4_src_k21116.cpp
//  final4_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//テンプレート画像の個数
#define TEMPLATE_QUANITY (8)

//差分配列の個数
#define DIFFERENCE_INDEX (8)

//差分の和の絶対値の閾値
#define TH_DIFFERENCE (5000)

int main (int argc, const char * argv[]){
    //右隣のテンプレートの番号
    int tmp_num[8];
    
    //テンプレート画像の読み込み
    cv::Mat template_img[TEMPLATE_QUANITY];
    char buf[256];
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        sprintf(buf, "template-%d.jpg", i);
        template_img[i] = cv::imread(buf);
        
        //画像が読めなかったとき
        if(template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0;
        }
    }
    
    //グレースケール画像
    cv::Mat template_gray_img[TEMPLATE_QUANITY];
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        cv::cvtColor(template_img[i], template_gray_img[i], cv::COLOR_BGR2GRAY);
    }
    
    //基準のテンプレート画像
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        //差分の最小値とインデックス番号
        int min_diff = INT_MAX;
        int min_diff_index;
        
        //差分
        int diff[8];
        
        //差分の初期化
        for (int d=0; d<DIFFERENCE_INDEX; d++) {
            diff[d] = 0;
        }
        
        //右隣のテンプレート画像
        for (int j=0; j<TEMPLATE_QUANITY; j++) {
            
            //縦方向の画素のみを走査
            for (int y=0; y<template_gray_img[i].rows; y++) {
                //画素値の取得
                unsigned char s_right = template_gray_img[i].at<uchar>(y, template_gray_img[i].cols-1);
                unsigned char s_left = template_gray_img[j].at<uchar>(y, 0);
                
                //右端、左端の差分を絶対値にして足す
                diff[j] += abs(s_right - s_left);
            }
        }
        
        //差分の最小値とそのインデックス番号を取得
        for (int d=0; d<DIFFERENCE_INDEX; d++) {
            if (min_diff > diff[d]) {
                min_diff = diff[d];
                min_diff_index = d;
            }
        }
        
        //閾値を利用して右隣の画像があるかを判定し、あった場合その画像を配列に格納
        if (min_diff < TH_DIFFERENCE) {
            tmp_num[i] = min_diff_index;
        }else {
            tmp_num[i] = -1;
        }
    }
    
    //結果の出力
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        printf("%d => %d\n", i, tmp_num[i]);
    }
    
    return 0;
}
