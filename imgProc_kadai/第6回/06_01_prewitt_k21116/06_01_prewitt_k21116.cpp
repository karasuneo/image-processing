//
//  gaussian.cpp
//  avv_filter
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/06_01_input_k21116.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    //グレースケール化
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    cv::Mat dst_img;
    
    double filter_h[] = {-1., -1., -1.,
                          0., 0., 0.,
                          1., 1., 1.
    };
    
    
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    //正規化（やらないと画素値が255を超えるため）
    //cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::Mat tmp_img;
    cv::filter2D(gray_img, tmp_img, CV_64F, kernel);
    
    //convertScaleAbs:絶対値をとり適切な倍率で値を変換するOpenCV関数
    //-8bit unsigned 出力画像(グレースケール)に変換される
    cv::convertScaleAbs(tmp_img, dst_img);
    
    //cv::cvtColor(tmp_img, dst_img, cv::COLOR_BGR2GRAY);

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
