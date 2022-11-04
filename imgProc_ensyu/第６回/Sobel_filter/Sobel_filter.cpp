//
//  filter2D.cpp
//  
//
//  Created by k21116kk on 2022/05/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../Debug/apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* arg[]){
    
    //imread:ファイルから画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    
    //画像が開けない時
    if (src_img.empty()) {
        fprintf(stderr, "Fire is not opened\n");
        return (-1);
    }
    
    //出力画像のメモリ確保(グレスケ化してから)
    cv::Mat dst_img;
    //かヴシアンフィルタ
    double filter_h[] = {-1., 0., 1.,
                         -2., 0., 2.,
                         -1., 0., 1.
    };
    
    //配列をフィルタ行列keneralに変換
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    //正規化（やらないと画素値が255を超えるため）
    //cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::Mat tmp_img;
    cv::filter2D(src_img, tmp_img, CV_64F, kernel);
    
    //convertScaleAbs:絶対値をとり適切な倍率で値を変換するOpenCV関数
    //-8bit unsigned 出力画像(グレースケール)に変換される
    cv::convertScaleAbs(tmp_img, dst_img);
    

    //画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
//ソーベルフィルタ関数
//cv::Sobel(入力画像, 出力画像, 深さ. 横, 縦);
//横方向なら　cv::Sobel(src_image, dst_image, CV_32F. 1, 0);
//縦方向なら　cv::Sobel(src_image, dst_image, CV_32F. 0, 1);
