//
//  filter2D.cpp
//
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "issue_input1.jpg"
#define FILE_NAME2 "issue_input2.jpg"
#define THERESHOLD (20)//閾値
#define FILTER_SIZE (5)



#define WINDOW_NAME_INPUT1 "input1"
#define WINDOW_NAME_INPUT2 "input2"
#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    
    //画像が開けない時
    if (src_img1.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    if (src_img2.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //メモリの確保
    cv::Mat sub_img = cv::Mat(src_img1.size(), CV_8UC1);
    cv::Mat gaussian_img = cv::Mat(src_img2.size(), CV_8UC1);
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC3);
    
    //ガウシアンフィルタ
    cv::GaussianBlur(src_img2, gaussian_img, cv::Size(FILTER_SIZE, FILTER_SIZE), 0);
    
    
    
    int x, y;
    
    //画素の走査
    for(y=0; y<src_img1.rows; y++){
        for(x=0; x<src_img1.cols; x++){
            //画素の取得
            int s1 = (int)src_img1.at<unsigned char>(y, x);
            int s_gau = (int)gaussian_img.at<unsigned char>(y, x);
            
            //差の所得
            int s_result = abs(s1 - s_gau);
            
            //出力画像へ変換
            sub_img.at<unsigned char>(y, x) = s_result;
            
            //閾値をもとに画像を比較
            if (s_result > THERESHOLD) {
                s_result = 255;
            }else{
                s_result = 0;
            }
            //白い部分を赤色に変換
            result_img.at<cv::Vec3b>(y, x)[2] = s_result;
            
        }
    }
    
    
    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT1, src_img1);
    cv::imshow(WINDOW_NAME_INPUT2, src_img2);
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    
    return 0;
    
}


//入力画像２に３５７９をかけてどれが近いか　絶対値をかけて弾く
//cv::GaussianBlur(src_img, dst_img, cv::Size(FILTER_SIZE, FILTER_SIZE), 0);
