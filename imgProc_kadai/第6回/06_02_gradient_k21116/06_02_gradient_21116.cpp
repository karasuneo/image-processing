//
//  gaussian.cpp
//  avv_filter
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
//#include <math.h>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/06_02_input_k21116.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_ONE "output1"
#define WINDOW_NAME_OUTPUT_TWO "output2"
#define WINDOW_NAME_OUTPUT_THREE "output3"
//#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, const char* arg[]){
    
    int i, x, y;//アクセス用の変数
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat tmp_img;
    cv::Mat tmp_h_img;
    cv::Mat tmp_v_img;
    cv::Mat H_img;
    cv::Mat V_img;
    cv::Mat G_img;
    //微分フィルタ(横)
    double filter_h[] = {0., 0., 0.,
                         1., 0., -1.,
                         0., 0., 0.
    };
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_h = cv::Mat(3, 3, CV_64F, filter_h);
    
    //正規化（やらないと画素値が255を超えるため）
    //cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    
    //フィルタの計算
    cv::filter2D(src_img, H_img, CV_64F, kernel_h);
    
    //convertScaleAbs:絶対値をとり適切な倍率で値を変換するOpenCV関数
    //-8bit unsigned 出力画像(グレースケール)に変換される
    cv::convertScaleAbs(H_img, tmp_h_img);
    
    //微分フィルタ(縦)
    double filter_v[] = {0., -1., 0.,
                         0.,  0., 0.,
                         0.,  1., 0.
    };
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel_v = cv::Mat(3, 3, CV_64F, filter_v);
    
    //正規化（やらないと画素値が255を超えるため）
    //cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    
    //フィルタの計算
    cv::filter2D(src_img, V_img, CV_64F, kernel_v);
    
    //convertScaleAbs:絶対値をとり適切な倍率で値を変換するOpenCV関数
    //-8bit unsigned 出力画像(グレースケール)に変換される
    cv::convertScaleAbs(V_img, tmp_v_img);
    
    //画素の走査
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            double s_h = tmp_h_img.at<unsigned char>(y, x);
            double s_v = tmp_v_img.at<unsigned char>(y, x);
            
            //unsigned char s_d = src_img.at<unsigned char>(y, x);
            
            dst_img.at<uchar>(y, x) = sqrt((s_h)*(s_h) + (s_v)*(s_v));
            
        }
    }
    

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_ONE, tmp_h_img);
    //cv::imshow(WINDOW_NAME_OUTPUT_TWO, tmp_v_img);
    cv::imshow(WINDOW_NAME_OUTPUT_THREE, dst_img);
    cv::waitKey();
    
    return 0;
}
