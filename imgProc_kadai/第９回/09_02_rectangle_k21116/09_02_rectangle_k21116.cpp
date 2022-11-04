//
//  contour4student.cpp
//
//
//  Created by Masashi Morimoto on 2022/06/07.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME_ONE "sample.jpg"
#define FILE_NAME_TWO "sample_rotate.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT_ONE "input1"
#define WINDOW_NAME_INPUT_TWO "input2"
#define WINDOW_NAME_BINARY_ONE "binary1"
#define WINDOW_NAME_BINARY_TWO "binary2"
#define WINDOW_NAME_OUTPUT_ONE "output1"
#define WINDOW_NAME_OUTPUT_TWO "output2"


//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_one_img, src_two_img, gray_one_img, bin_one_img, tmp_one_img, dst_one_img, gray_two_img, bin_two_img, tmp_two_img, dst_two_img;
    
    //2. 輪郭の座標リストの宣言 (New!)
    std::vector< std::vector< cv::Point > > contours_one;
    std::vector< std::vector< cv::Point > > contours_two;
    
    //3. 画像の入力 (カラーで入力)
    src_one_img = cv::imread(FILE_NAME_ONE);
    src_two_img = cv::imread(FILE_NAME_TWO);
    if (src_one_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    if (src_two_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を出力画像にコピー (New!)
    dst_one_img = src_one_img.clone();
    dst_two_img = src_two_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_one_img, gray_one_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(src_two_img, gray_two_img, cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定しきい値で実装．しきい値: 100)
    cv::threshold(gray_one_img, bin_one_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::threshold(gray_two_img, bin_two_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    //二値画像コピー (New!)
    //輪郭追跡でbin_imgが加工されてしまうため
    //clone():画像のコピーを作成するためのメンバ関数
    tmp_one_img = bin_one_img.clone();
    tmp_two_img = bin_two_img.clone();
    
    //7. 輪郭追跡 (New!)
    cv::findContours(tmp_one_img, contours_one, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    cv::findContours(tmp_two_img, contours_two, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    //8. 輪郭の描画 (New!)
    
    //8.1輪郭数の表示
    for (int i=0; i<contours_one.size(); i++) {
        double L, S, R;
        L = cv::arcLength(contours_one[i], true);
        S = cv::contourArea(contours_one[i]);
        R = (4*M_PI*S) / (L*L);
        if (S <= 5000 && S >=4000) {
            if (R < 0.8) {
                printf("aaa:%lf\n", R);
                printf("%d\n", i);
                cv::drawContours(dst_one_img, contours_one, i, CV_RGB(255, 0, 255), -1);
            }
        }
    }
    for (int i=0; i<contours_two.size(); i++) {
        double L, S, R;
        L = cv::arcLength(contours_two[i], true);
        S = cv::contourArea(contours_two[i]);
        R = (4*M_PI*S) / (L*L);
        if (S <= 5000 && S >=4000) {
            if (R < 0.8) {
                printf("aaa:%lf\n", R);
                printf("%d\n", i);
                cv::drawContours(dst_two_img, contours_two, i, CV_RGB(255, 0, 255), -1);
            }
        }
    }
    
    //9. 表示
    /*cv::imshow(WINDOW_NAME_INPUT_ONE, src_one_img);
    cv::imshow(WINDOW_NAME_INPUT_TWO, src_two_img);
    cv::imshow(WINDOW_NAME_BINARY_ONE, bin_one_img);
    cv::imshow(WINDOW_NAME_BINARY_TWO, bin_two_img);
     */
    cv::imshow(WINDOW_NAME_OUTPUT_ONE, dst_one_img);
    cv::imshow(WINDOW_NAME_OUTPUT_TWO, dst_two_img);
    cv::waitKey();
    
    return 0;
}

