#include <iostream>
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//ȷ��37��ģ�������ƫ����
	int OffSetX[37] =
	{ -1, 0, 1,
	-2, -1, 0, 1, 2,
	-3, -2, -1, 0, 1, 2, 3,
	-3, -2, -1, 0, 1, 2, 3,
	-3, -2, -1, 0, 1, 2, 3,
	-2, -1, 0, 1, 2,
	-1, 0, 1 };
	int OffSetY[37] =
	{
		-3, -3, -3,
		-2, -2, -2, -2, -2,
		-1, -1, -1, -1, -1, -1, -1,
		0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3
	};

	Mat src_img = imread("C:\\Users\\Tim\\Desktop\\a.jpg");
	namedWindow("src_img");
	imshow("src_img", src_img);

	Mat gray_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY);
	Mat dst_img;
	dst_img.create(src_img.size(), CV_8UC1);

	uchar same, centergray, thread = 15;
	//same37����������λ�õĻҶ�ֵ��಻������ֵ�ĸ���������
	//centergray����λ�ûҶ�ֵ��
	//thread�趨����ֵ��

	for (int i = 3; i < src_img.cols - 3; i++)
		for (int j = 3; j < src_img.rows - 3; j++)
		{
			same = 0;
			centergray = 0;
			for (int k = 0; k < 37; k++)
			{
				centergray = gray_img.at<uchar>(j, i);
				if (gray_img.at<uchar>(j + OffSetX[k], i + OffSetY[k]) < (centergray + thread)
					&& gray_img.at<uchar>(j + OffSetX[k], i + OffSetY[k]) > (centergray - thread))
					same++;
			}

			if (same < 27)
				dst_img.at<uchar>(j, i) = 255;
			else
				dst_img.at<uchar>(j, i) = 0;
		}

	namedWindow("dst_img");
	imshow("dst_img", dst_img);
	waitKey(0);
	return 0;
}