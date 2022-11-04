//
//  main.cpp
//  templateMatching4student
//
//  Created by sawano on 2015/07/05.
//  Modified by Tsukada  2021.07.06
//  Copyright (c) 2015年 AIT. All rights reserved.
//


#include <iostream>
#include <opencv2/opencv.hpp>

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_TMP "output1"
#define WINDOW_NAME_OUTPUT_COM "output2"
#define WINDOW_NAME_OUTPUT_RES "output3"

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "gazoDora.jpg"

//テンプレート画像
#define TEMPLATE_IMG_FILE "red.jpg"
int main (int argc, const char * argv[]){
    cv::Mat src_img, template_img, compare_img, result_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    float min = 100;
    
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_GRAYSCALE);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //テンプレート画像
    template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_GRAYSCALE);
    
    
       
    //類似度マップ (1チャンネル)
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
    
       
    //結果画像
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); //画像のコピー
       
       
       
    //テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");

    // ここに書く
    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
          
    fprintf(stderr, "テンプレートマッチングの終了\n");
       
    for (int y=0; y<compare_img.rows; y++) {
        for (int x=0; x<compare_img.cols; x++) {
            s = compare_img.at<float>(y, x);
            s = 0;
        }
    }
       
    //探索画像の描画
    cv::imshow(WINDOW_NAME_INPUT, src_img); //入力画像
    cv::imshow(WINDOW_NAME_OUTPUT_TMP, template_img); //入力画像
    cv::imshow(WINDOW_NAME_OUTPUT_COM, compare_img); //入力画像
    cv::imshow(WINDOW_NAME_OUTPUT_RES, result_img); //結果画像
       //キー入力待ち
    cv::waitKey(0);
    return 0;
    
}

