//
//  filter2D.cpp
//  
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../Debug/dot_gray_rectangle.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_ONE "output1"
#define WINDOW_NAME_OUTPUT_TWO "output2"
#define WINDOW_NAME_OUTPUT_TFREE "output3"

#define FILTER_SIZE (20)


int main(int argc, const char* arg[]){
    int i, x, y;//アクセス用の変数
    
    int hist[COLOR_MAX];
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //グレースケール化してメモリ確保
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::Mat smooth_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    

    double filter_h[FILTER_SIZE*FILTER_SIZE];
    for (int i=0; i<(FILTER_SIZE*FILTER_SIZE)-1; i++) {
        filter_h[i] = 1./(double)(FILTER_SIZE*FILTER_SIZE);
    }
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_h = cv::Mat(FILTER_SIZE, FILTER_SIZE, CV_32F, filter_h);
    //正規化（やらないと画素値が255を超えるため）
    cv::normalize(kernel_h, kernel_h, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(gray_img, smooth_img, -1, kernel_h);

    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s =smooth_img.at<unsigned char>(y, x);
            
            //輝度値の値に応じて二色化
            if ((int)s < 75) {
                s = 255;
                dst_img.at<uchar>(y, x) = s;
            }else{
                s = 0;
                dst_img.at<uchar>(y, x) = s;
            }
        }
    }
    
    for (y=0; y<dst_img.rows; y++) {
        for (x=0; x<dst_img.cols; x++) {
            //画素値の取得
            unsigned char s = dst_img.at<unsigned char>(y, x);
            
            hist[(int)s]++;//画素数の計算　画素値(0〜255)
        }
    }
    
    
    
    
    for (i=0; i<COLOR_MAX; i++) {
        printf("%d %d\n", i, hist[i]);//左:輝度値　右:その輝度値の画素数
    }
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_ONE, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT_TWO, dst_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_TFREE, smooth_img);
    
    
    //cv::imshow(WINDOW_NAME_OUTPUT_TFREE, dst_img);
    cv::waitKey();
    
    return 0;
}
