//
//  final1_src_k21116.cpp
//  final1_src_k21116
//
//  Created by Yusei Mizutani on 2022/07/29.
//


#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "gazoDora.jpg"

//テンプレート画像
#define TEMPLATE_IMG1_FILE "green.jpg"
#define TEMPLATE_IMG2_FILE "red.jpg"
#define TEMPLATE_IMG3_FILE "star.jpg"
#define TEMPLATE_IMG4_FILE "yellow.jpg"
int main (int argc, const char * argv[]){
    cv::Mat src_img, template_img_green, template_img_red, template_img_star, template_img_yellow, compare_img_green, compare_img_red, compare_img_star, compare_img_yellow, result_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    float min = 100;
    
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //テンプレート画像
    template_img_green = cv::imread(TEMPLATE_IMG1_FILE, cv::IMREAD_COLOR);
    template_img_red = cv::imread(TEMPLATE_IMG2_FILE, cv::IMREAD_COLOR);
    template_img_star = cv::imread(TEMPLATE_IMG3_FILE, cv::IMREAD_COLOR);
    template_img_yellow = cv::imread(TEMPLATE_IMG4_FILE, cv::IMREAD_COLOR);
    
    
       
       //類似度マップ (1チャンネル)
    compare_img_green = cv::Mat(cv::Size(src_img.rows - template_img_green.rows + 1, src_img.cols - template_img_green.cols + 1), CV_32F, 1);
    compare_img_red = cv::Mat(cv::Size(src_img.rows - template_img_red.rows + 1, src_img.cols - template_img_red.cols + 1), CV_32F, 1);
    compare_img_star = cv::Mat(cv::Size(src_img.rows - template_img_star.rows + 1, src_img.cols - template_img_star.cols + 1), CV_32F, 1);
    compare_img_yellow = cv::Mat(cv::Size(src_img.rows - template_img_yellow.rows + 1, src_img.cols - template_img_yellow.cols + 1), CV_32F, 1);
       
       //結果画像
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); //画像のコピー
       
       //ここまでが初期化 (前処理)
       //------------------------------------------------------------
       
       
    //テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");

    // ここに書く
    cv::matchTemplate(src_img, template_img_green, compare_img_green, cv::TM_SQDIFF_NORMED);
    cv::matchTemplate(src_img, template_img_red, compare_img_red, cv::TM_SQDIFF_NORMED);
    cv::matchTemplate(src_img, template_img_star, compare_img_star, cv::TM_SQDIFF_NORMED);
    cv::matchTemplate(src_img, template_img_yellow, compare_img_yellow, cv::TM_SQDIFF_NORMED);
          
    fprintf(stderr, "テンプレートマッチングの終了\n");
       
    //類似度マップの最小値最大値の計算
    
      
    // ここに書く
    
    
    for (int y=0; y<compare_img_green.rows; y++) {
        for (int x=0; x<compare_img_green.cols; x++) {
            s = compare_img_green.at<float>(y, x);
            if (s <= 0.1) {
                //長方形の表示
                cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img_green.cols, y + template_img_green.rows), CV_RGB(0, 255, 0), 3);
                
                fprintf(stderr, "%d, %d\n", x, y);
            }
        }
    }
    
    for (int y=0; y<compare_img_red.rows; y++) {
        for (int x=0; x<compare_img_red.cols; x++) {
            s = compare_img_red.at<float>(y, x);
            if (s <= 0.1) {
                //長方形の表示
                cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img_red.cols, y + template_img_red.rows), CV_RGB(255, 0, 0), 3);
                
                fprintf(stderr, "%d, %d\n", x, y);
            }
        }
    }
    
    for (int y=0; y<compare_img_star.rows; y++) {
        for (int x=0; x<compare_img_star.cols; x++) {
            s = compare_img_star.at<float>(y, x);
            if (s <= 0.1) {
                //長方形の表示
                cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img_star.cols, y + template_img_star.rows), CV_RGB(255, 255, 0), 3);
                
                fprintf(stderr, "%d, %d\n", x, y);
            }
        }
    }
    
    for (int y=0; y<compare_img_red.rows; y++) {
        for (int x=0; x<compare_img_red.cols; x++) {
            s = compare_img_yellow.at<float>(y, x);
            if (s <= 0.1) {
                //長方形の表示
                cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img_yellow.cols, y + template_img_yellow.rows), CV_RGB(255, 0, 255), 3);
                
                fprintf(stderr, "%d, %d\n", x, y);
            }
        }
    }
    
    
    

       
      
       //探索画像の描画
    cv::imshow("input", src_img); //入力画像
    cv::imshow("template", template_img_green); //テンプレート画像
    cv::imshow("result", result_img); //結果画像
    //キー入力待ち
    cv::waitKey(0);
    return 0;
    
}
