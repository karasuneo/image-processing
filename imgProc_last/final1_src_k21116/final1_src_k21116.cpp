//
//  final1_src_k21116.cpp
//  final1_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "input1.jpg"

//テンプレート画像の個数
#define TEMPLATE_QUANITY (8)

int main (int argc, const char * argv[]){
    //入力画像
    cv::Mat src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    
    //画像が読めなかったとき
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
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
    
    //類似度マップの作成
    cv::Mat compare_img[TEMPLATE_QUANITY];
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        compare_img[i] = cv::Mat(cv::Size(src_img.rows - template_img[i].rows + 1, src_img.cols - template_img[i].cols + 1), CV_32F, 1);
    }
    
    //テンプレートマッチング
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        cv::matchTemplate(src_img, template_img[i], compare_img[i], cv::TM_SQDIFF_NORMED);
    }
    
    //最小値，最大値
    double min_val, max_val;
    
    //最小値の位置，最大値の位置
    cv::Point min_loc, max_loc;
    
    //最小値の位置，最大値の位置の出力
    for (int i=0; i<TEMPLATE_QUANITY; i++) {
        cv::minMaxLoc (compare_img[i], &min_val, &max_val, &min_loc, &max_loc);
        printf("%d: %d, %d\n", i, min_loc.x, min_loc.y);
    }
    
    return 0;
    
}
