#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<ctime>
#include<thread>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<opencv2/opencv.hpp>
//CODER BY Vistyxio POWERD BY VS2019
using namespace std;
using namespace cv;

string str1 = "final\\final";
string num;
int n = 1, chann;
string str2 = ".png";
string name;
vector<Mat> sequ;

void myRGB(Mat& src, Mat& dst, vector<Point> vec, int a, int b, int per) {
	for (register int i = 0; i <= 255; i++) {
		for (auto v : vec) {
			if (chann == 4) {
				dst.at<Vec4b>(v.x, v.y)[a] = 255 - i;
				dst.at<Vec4b>(v.x, v.y)[b] = i;
			} else {
				dst.at<Vec3b>(v.x, v.y)[a] = 255 - i;
				dst.at<Vec3b>(v.x, v.y)[b] = i;
			}
			
		}
		num = to_string(n);
		name = str1 + num + str2;
		double p = double(per) / 100.0;
		addWeighted(dst, p, src, 1.0 - p, 0, dst);

		imwrite(name, dst);
		cout << setprecision(2) << fixed << double(100.0 * double(n) / 768.0) << "%" << endl;
		n++;
	}
}

void clearr(Mat& dst, vector<Point> vec) {
	for (auto v : vec) {
		if (chann == 4) {
			dst.at<Vec4b>(v.x, v.y)[0] = 0;
			dst.at<Vec4b>(v.x, v.y)[1] = 0;
			dst.at<Vec4b>(v.x, v.y)[2] = 0;
			dst.at<Vec4b>(v.x, v.y)[3] = 255;
		} else {
			dst.at<Vec3b>(v.x, v.y)[0] = 0;
			dst.at<Vec3b>(v.x, v.y)[1] = 0;
			dst.at<Vec3b>(v.x, v.y)[2] = 0;
		}
		
	}
}

void shold() {
	string str;
	Mat src = sequ.back();
	Mat shold_src;
	while (1) {
		cout << "输入a阈值以使用THRESH_BINARY进行二值化" << endl;
		cout << "输入b阈值以使用THRESH_BINARY_INV进行二值化" << endl;
		cout << "通俗理解a是让黑色更黑 白色更白 b是相反 可以理解成a的反色" << endl;
		cout << "例如a120" << endl;
		cout << endl << "范围0-255 一般在100-220" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		if (str.substr(0, 1) != "a" && str.substr(0, 1) != "b") continue;
		if (str.substr(0, 1) == "a") {
			threshold(src, shold_src, saturate_cast<uchar>(stoi(str.substr(1))), 255, THRESH_BINARY);
		} else if (str.substr(0, 1) == "b") {
			threshold(src, shold_src, saturate_cast<uchar>(stoi(str.substr(1))), 255, THRESH_BINARY_INV);
		}
		imshow("threshold", shold_src);
		waitKey(5);
	}
	sequ.emplace_back(shold_src);
	destroyAllWindows();
}

void median() {
	string str;
	Mat src = sequ.back();
	Mat median_src;
	while (1) {
		cout << endl << "输入数字进行中值滤波 大于0 必须为奇数" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		medianBlur(src, median_src, stoi(str));
		imshow("medianBlur", median_src);
		waitKey(5);
	}
	sequ.emplace_back(median_src);
	destroyAllWindows();
}

void erosion() {
	string str;
	Mat src = sequ.back();
	Mat erode_src;
	Mat kernel;
	while (1) {
		cout << endl << "输入数字定义内核进行腐蚀操作 大于0 必须为奇数" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		kernel = getStructuringElement(MORPH_RECT, Size(stoi(str), stoi(str)));
		erode(src, erode_src, kernel);
		imshow("erode", erode_src);
		waitKey(5);
	}
	sequ.emplace_back(erode_src);
	destroyAllWindows();
}

void dilation() {
	string str;
	Mat src = sequ.back();
	Mat dilate_src;
	Mat kernel;
	while (1) {
		cout << endl << "输入数字定义内核进行膨胀操作 大于0 必须为奇数" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		kernel = getStructuringElement(MORPH_RECT, Size(stoi(str), stoi(str)));
		dilate(src, dilate_src, kernel);
		imshow("dilate", dilate_src);
		waitKey(5);
	}
	sequ.emplace_back(dilate_src);
	destroyAllWindows();
}

void open() {
	string str;
	Mat src = sequ.back();
	Mat open_src;
	Mat kernel;
	while (1) {
		cout << endl << "输入数字定义内核进行开操作 大于0 必须为奇数" << endl;
		cout << "可以消除白色的小点 去除小的干扰块" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		kernel = getStructuringElement(MORPH_RECT, Size(stoi(str), stoi(str)));
		morphologyEx(src, open_src, MORPH_OPEN, kernel);
		imshow("MORPH_OPEN", open_src);
		waitKey(5);
	}
	sequ.emplace_back(open_src);
	destroyAllWindows();
}

void close() {
	string str;
	Mat src = sequ.back();
	Mat close_src;
	Mat kernel;
	while (1) {
		cout << endl << "输入数字定义内核进行闭操作 大于0 必须为奇数" << endl;
		cout << "可以消除黑色的小块 填充闭合区域" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		kernel = getStructuringElement(MORPH_RECT, Size(stoi(str), stoi(str)));
		morphologyEx(src, close_src, MORPH_CLOSE, kernel);
		imshow("MORPH_CLOSE", close_src);
		waitKey(5);
	}
	sequ.emplace_back(close_src);
	destroyAllWindows();
}

void gradient() {
	string str;
	Mat src = sequ.back();
	Mat gradient_src;
	Mat kernel;
	while (1) {
		cout << endl << "输入数字定义内核进行梯度操作 大于0 必须为奇数" << endl;
		cout << "梯度就是膨胀和腐蚀的差 可用来保留轮廓" << endl;
		cout << "一般在10以内" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		kernel = getStructuringElement(MORPH_RECT, Size(stoi(str), stoi(str)));
		morphologyEx(src, gradient_src, MORPH_GRADIENT, kernel);
		imshow("MORPH_GRADIENT", gradient_src);
		waitKey(5);
	}
	sequ.emplace_back(gradient_src);
	destroyAllWindows();
}

void canny() {
	string str;
	int n, m;
	Mat src = sequ.back();
	Mat canny_src;
	while (1) {
		cout << endl << "输入三个数字进行Canny边缘检测 大于0" << endl;
		cout << "可以对输入图像进行边缘检测" << endl;
		cout << "低于阈值1的像素点会被认为不是边缘" << endl;
		cout << "高于阈值2的像素点会被认为是边缘" << endl;
		cout << "在阈值1和阈值2之间的像素点,若与第2步得到的边缘像素点相邻，则被认为是边缘，否则被认为不是边缘" << endl;
		cout << "调节完成输入ok" << endl;
		cout << "输入exit退出 不保留修改" << endl;
		cout << "先输入阈值1" << endl;
		cin >> str;
		if (str == "ok") break;
		if (str == "exit") {
			destroyAllWindows();
			return;
		}
		cout << "再输入阈值2" << endl;
		cin >> n;
		cout << "再输入内核大小 一般是3" << endl;
		cin >> m;
		Canny(src, canny_src, stoi(str), n, m, false);
		imshow("Canny", canny_src);
		waitKey(5);
	}
	sequ.emplace_back(canny_src);
	destroyAllWindows();
}

int main() {
	system("title 图片RGB化生成器");
	Mat src, dst_src, dst, gray_src, element = getStructuringElement(MORPH_RECT, Size(3, 3));
	string filePath, n, sttr;
	int a = 0, per = 0;
	vector<Point> vec;
	cout << "RGB图片制作器 可以把图片变成RGB变化的gif" << endl;
	cout << "建议先阅读readme.txt了解几种基本的操作" << endl;
	cout << "输入路径或拖动图片到此" << endl;
	cout << "新增功能:可输入或拖入由魔棒工具生成的ncc配置文件" << endl;
	getline(cin, filePath);
	if (filePath[0] == '"') filePath = filePath.substr(1, filePath.length() - 2);
	if (filePath.substr(filePath.length() - 3, 3) == "ncc") {
		ifstream infile;
		string picPath;
		infile.open(filePath);
		infile >> picPath;
		Mat src = imread(picPath, -1);
		Mat dst = imread(picPath, -1);
		chann = dst.channels();
		vector<Point> ROIArea;
		int x, y;
		infile >> x;
		while (x != -1) {
			infile >> y;
			ROIArea.emplace_back(Point(x, y));
			infile >> x;
		}

		do {
			cout << "设置叠加百分比(0至100的整数)" << endl << "100是全部使用RGB 0是不使用RGB。" << endl;
			cin >> per;
		} while (per < 0 || per > 100);

		system("mkdir final");
		clearr(dst, ROIArea);
		myRGB(src, dst, ROIArea, 2, 1, per);
		myRGB(src, dst, ROIArea, 1, 0, per);
		myRGB(src, dst, ROIArea, 0, 2, per);
		system("ffmpeg -i final\\final%d.png -vf palettegen palette.png -y");
		system("ffmpeg -thread_queue_size 96 -i final\\final%d.png -i palette.png -filter_complex \"[0:v]setpts=0.05*PTS[v];[v][1:v]paletteuse\" final.gif -y");
		system("rd /s /q final");
		system("del palette.png");
		system("ren final.gif %date:~0,4%_%date:~5,2%_%date:~8,2%_%time:~6,2%_%time:~9,2%.gif");
		cout << "完成" << endl;
		system("ping -n 1 127.0.0.1>nul");
		return 0;
	}


	src = imread(filePath, -1);
	chann = src.channels();

	do {
		cout << "1黑底2白底" << endl;
		cin >> a;
		if (a == 1) {
			dst = Mat::zeros(src.rows, src.cols, src.type());
		} else if (a == 2) {
			dst = Mat(src.rows, src.cols, src.type(), Scalar(255, 255, 255));
		}
	} while (a != 1 && a != 2);

	do {
		cout << "设置叠加百分比(0至100)" << endl << "100是全部使用RGB 0是不使用RGB。" << endl;
		cin >> per;
	} while (per < 0 || per > 100);

	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	sequ.emplace_back(gray_src);

	while (1) {
		system("cls");
		destroyAllWindows();
		cout << "提示:不清楚功能请勿擅用 建议百度" << endl;
		cout << "包含文字或图片较小建议直接二值化然后ok" << endl;
		cout << "输入序号选择要进行的步骤" << endl << endl;
		cout << "1.二值化 将灰度图转换成只有纯黑和纯白的图像" << endl;
		cout << "2.中值滤波 用来除去斑点噪声和椒盐噪声" << endl;
		cout << "3.腐蚀 可以认为是将黑色区域扩大" << endl;
		cout << "4.膨胀 可以认为是将白色区域扩大" << endl;
		cout << "5.开操作 可以消除白色的小点 去除小的干扰块" << endl;
		cout << "6.闭操作 可以消除黑色的小块 填充闭合区域" << endl;
		cout << "7.梯度 就是膨胀和腐蚀的差 可用来保留轮廓" << endl;
		cout << "8.Canny边缘检测" << endl;
		
		cout << "输入yl来预览当前图像" << endl;
		cout << endl << "输入fh数字进行反悔" << endl;
		cout << "例如fh6返回到第6步" << endl;

		cout << endl << "输入ok退出图像操作" << endl;
		cin >> n;
		if (n.substr(0, 2) == "fh") {
			while (sequ.size() != (stoi(n.substr(2)) + size_t(1))) sequ.pop_back();
			continue;
		}
		if (n == "yl") {
			cout << "将焦点放到预览图上 按任意键退出预览" << endl;
			imshow("预览", sequ.back());
			waitKey(0);
			continue;
		}

		if (n == "1") {
			shold();
		} else if (n == "2") {
			median();
		} else if (n == "3") {
			erosion();
		} else if (n == "4") {
			dilation();
		} else if (n == "5") {
			open();
		} else if (n == "6") {
			close();
		} else if (n == "7") {
			gradient();
		} else if (n == "8") {
			canny();
		} else if (n == "ok") break;
	}


	dst_src = sequ.back();
	destroyAllWindows();
	for (register int i = 0; i < dst_src.rows; i++) {
		for (register int j = 0; j < dst_src.cols; j++) {
			if (!dst_src.at<uchar>(i, j)) {
				vec.emplace_back(Point(i, j));
			}
		}
	}

	system("mkdir final");
	clearr(dst, vec);
	myRGB(src, dst, vec, 2, 1, per);
	myRGB(src, dst, vec, 1, 0, per);
	myRGB(src, dst, vec, 0, 2, per);
	system("ffmpeg -i final\\final%d.png -vf palettegen palette.png -y");
	system("ffmpeg -thread_queue_size 96 -i final\\final%d.png -i palette.png -filter_complex \"[0:v]setpts=0.05*PTS[v];[v][1:v]paletteuse\" final.gif -y");
	system("rd /s /q final");
	system("del palette.png");
	system("ren final.gif %date:~0,4%_%date:~5,2%_%date:~8,2%_%time:~6,2%_%time:~9,2%.gif");
	cout << "完成" << endl;
	system("ping -n 1 127.0.0.1>nul");
	return 0;
}