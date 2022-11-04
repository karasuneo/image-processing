//
//  dft4student.cpp
//
//  Created by sawano on 2020/07/07.
//  Copyright © 2020年 AIT. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル名
#define FILE_NAME "gem1.jpg"

//ウィンドウ名
#define INPUT_WINDOW "input"
#define MAG_WINDOW "Magnitude"
#define RESULT_WINDOW "Result"

#define COLOR_MAX (256)




int main(int argc, const char * argv[]) {
    cv::Mat src_img, gray_img, dst_img;
    int hist[COLOR_MAX];

    //カラー画像(省略可能)
    //1. エッジ検出
    //1. 入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    //濃淡変換を指示
     //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //3. エッジ検出(cannyオペレータ)
    cv::Canny(gray_img, dst_img, 100, 200);
    
    for (int i=0; i<COLOR_MAX; i++) {
        hist[i] = 0;
    }
    //4. ヒストグラムの生成
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            uchar s = gray_img.at<uchar>(y,x); //画素値の取得
            hist[(int)s]++; //画素値に相当する配列の要素を加算 }
        }
    }
        
    //5. コンソールに出力
    for (int i=0; i<COLOR_MAX; i++) {
        printf("%d\n", hist[i]);
    }

    //画像の表示
    cv::imshow(INPUT_WINDOW, src_img);
    cv::imshow(RESULT_WINDOW, dst_img);
    
    //キー入力待ち
    cv::waitKey();
    
    return 0;
}
