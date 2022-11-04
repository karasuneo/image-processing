//
//  final5_src_k21116.cpp
//  final5_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//　参考資料：http://opencv.jp/cookbook/opencv_img.html
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define WINDOW_NAME_OUTPUT "output"

//テンプレート画像の個数
#define TEMPLATE_QUANITY (8)

//差分配列の個数
#define DIFFERENCE_INDEX (8)

//差分の和の閾値
#define TH_HORIZONAL_DIFFERENCE (5000)
//差分の和の閾値
#define TH_VERTICAL_DIFFERENCE (6600)

int main (int argc, const char * argv[]){
    
    //右隣、下隣のテンプレートの番号
    int tmp_horizonal_num[8], tmp_vertical_num[8];
    
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
        int min_horizonal_diff = INT_MAX;
        int min_vertical_diff = INT_MAX;
        int min_horizonal_diff_index, min_vertical_diff_index;
        
        //差分
        int diff_horizonal[8], diff_vertical[8];
        
        //差分の初期化
        for (int d=0; d<DIFFERENCE_INDEX; d++) {
            diff_horizonal[d] = 0;
            diff_vertical[d] = 0;
        }
        
        //比較するテンプレート画像
        for (int j=0; j<TEMPLATE_QUANITY; j++) {
            
            //縦方向の画素のみを走査(左右方向の繋がりについて)
            for (int y=0; y<template_gray_img[i].rows; y++) {
                //画素値の取得
                unsigned char s_right = template_gray_img[i].at<uchar>(y, template_gray_img[i].cols-1);
                unsigned char s_left = template_gray_img[j].at<uchar>(y, 0);
                
                //右端、左端の差分を絶対値にして足す
                diff_horizonal[j] += abs(s_right - s_left);
            }
            
            //横方向の画素のみを走査(上下方向の繋がりについて)
            for (int x=0; x<template_gray_img[i].rows; x++) {
                //画素値の取得
                unsigned char s_down = template_gray_img[i].at<uchar>(template_gray_img[i].rows-1, x);
                unsigned char s_up = template_gray_img[j].at<uchar>(0, x);
                
                //下、上の差分を絶対値にして足す
                diff_vertical[j] += abs(s_down - s_up);
            }
        }
        
        
        //差分の最小値とそのインデックス番号を取得
        for (int d=0; d<DIFFERENCE_INDEX; d++) {
            //左右方向について
            if (min_horizonal_diff > diff_horizonal[d]) {
                min_horizonal_diff = diff_horizonal[d];
                min_horizonal_diff_index = d;
            }
            
            //上下方向について
            if (min_vertical_diff > diff_vertical[d]) {
                min_vertical_diff = diff_vertical[d];
                min_vertical_diff_index = d;
            }
        }
        
        //閾値を利用して右隣の画像があるかを判定し、あった場合その画像を配列に格納
        //左右方向について
        if (min_horizonal_diff < TH_HORIZONAL_DIFFERENCE) {
            tmp_horizonal_num[i] = min_horizonal_diff_index;
        }else {
            tmp_horizonal_num[i] = -1;
        }
        
        //上下方向について
        if (min_vertical_diff < TH_VERTICAL_DIFFERENCE) {
            tmp_vertical_num[i] = min_vertical_diff_index;
        }else {
            tmp_vertical_num[i] = -1;
        }
    }
    
    //上半分、下半分の画像の順番を格納するための配列
    int order_up[4], order_down[4];
    
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        
        //下半分の画像の順番の並び替え
        if (tmp_vertical_num[i] == -1) {
            //右端の画像
            if (tmp_horizonal_num[i] == -1) {
                order_down[3] = i;
            }
            
            //1,2,3番目の画像
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_down[3]) {
                    order_down[2] = j;
                }
            }
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_down[2]) {
                    order_down[1] = j;
                }
            }
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_down[1]) {
                    order_down[0] = j;
                }
            }
            
        }
        
        //上半分の画像の順番の並び替え
        if (tmp_vertical_num[i] != -1) {
            //右端の画像
            if (tmp_horizonal_num[i] == -1) {
                order_up[3] = i;
            }
            
            //1,2,3番目の画像
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_up[3]) {
                    order_up[2] = j;
                }
            }
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_up[2]) {
                    order_up[1] = j;
                }
            }
            for (int j=0; j<TEMPLATE_QUANITY; j++) {
                if (tmp_horizonal_num[j] == order_up[1]) {
                    order_up[0] = j;
                }
            }
        }
    }
    
    //出力画像の定義
    cv::Mat dst_img = cv::Mat(template_img[0].size()*8, CV_8UC3);
    cv::Mat dst_up_img_h = cv::Mat(template_img[0].size()*4, CV_8UC3);
    cv::Mat dst_down_img_h = cv::Mat(template_img[0].size()*4, CV_8UC3);
    cv::Mat tmp_dst_img[4];
    
    for (int i=0; i<4; i++) {
        tmp_dst_img[i] = cv::Mat(template_img[0].size(), CV_8UC3);
    }
    
    //４つ角の画像を結合し、４枚の画像にする
    hconcat(template_img[order_up[0]], template_img[order_up[1]], tmp_dst_img[0]);
    hconcat(template_img[order_up[2]], template_img[order_up[3]], tmp_dst_img[1]);
    hconcat(template_img[order_down[0]], template_img[order_down[1]], tmp_dst_img[2]);
    hconcat(template_img[order_down[2]], template_img[order_down[3]], tmp_dst_img[3]);
    
    //上４枚、下４枚の画像の結合し、２枚の画像にする
    hconcat(tmp_dst_img[0], tmp_dst_img[1], dst_up_img_h);
    hconcat(tmp_dst_img[2], tmp_dst_img[3], dst_down_img_h);
    
    //上半分、下半分の画像の結合し、８枚の画像を１つの画像にする
    vconcat(dst_up_img_h, dst_down_img_h, dst_img);
    
    //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    
    cv::waitKey();
    
    return 0;
}
