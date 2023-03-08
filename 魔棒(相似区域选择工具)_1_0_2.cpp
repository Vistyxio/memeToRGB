#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string>
#include<thread>
#include<cstdio>
#include<opencv2/opencv.hpp>
//CODER BY Vistyxio POWERD BY VS2019
using namespace std;
using namespace cv;

int MagicThreshold = 15;
int f, chann;
Mat src, src_gray;
string filePath, temp, str;
vector<Point2d> ROIArea;

inline bool check(int org_x, int org_y, int x, int y, bool** flag) {
	if (x < 0 || y < 0 || x >= src.rows || y >= src.cols) return 0;
	if (abs(src_gray.at<uchar>(org_x, org_y) - src_gray.at<uchar>(x, y)) > MagicThreshold) return 0;
	if (flag[x][y] == 1) return 0;
	return 1;
}

string getFileName(string filePath) {
	string str;
	for (register long long i = filePath.length() - 1; i >= 0; i--) {
		if (filePath[i] == '\\') break;
		str += filePath[i];
	}
	reverse(str.begin(), str.end());
	return str;
}

void writeDAT(vector<Point2d> ROIArea) {
	ofstream outfile;
	if (f == 1) {
		outfile.open(temp, ios::out);
		outfile << filePath << endl;
	} else {
		outfile.open(temp, ios::out | ios::app);
	}
	for (auto i : ROIArea) {
		outfile << i.x << " " << i.y << endl;
	}
	outfile.close();
	cout << "配置文件写入完成" << endl;
}

void MagicWandTool(int org_x, int org_y) {
	Mat src_magic;
	src.copyTo(src_magic);

	int dir[4][2] = { 0,1,1,0,0,-1,-1,0 };
	bool** flag = new bool* [src.rows];
	for (register size_t i = 0; i < src.rows; i++) flag[i] = new bool[src.cols];
	queue<Point2d> MagicArea;
	
	MagicArea.push(Point2d(org_x, org_y));
	ROIArea.emplace_back(Point2d(org_x, org_y));
	flag[org_x][org_y] = 1;
	while (!MagicArea.empty()) {
		int now_x = MagicArea.front().x;
		int now_y = MagicArea.front().y;
		MagicArea.pop();
		
		for (register size_t i = 0; i < 4; i++) {
			int xx = now_x + dir[i][0];
			int yy = now_y + dir[i][1];
			if (check(org_x, org_y, xx, yy, flag)) {
				MagicArea.push(Point2d(xx, yy));
				ROIArea.emplace_back(Point2d(xx, yy));
				flag[xx][yy] = 1;
			}
		}
	}

	writeDAT(ROIArea);
	bool num = 0;
	for (auto i : ROIArea) {
		if (!num) {
			num = 1;
			if (chann == 4) {
				src_magic.at<Vec4b>(i.x, i.y)[0] = 80;
				src_magic.at<Vec4b>(i.x, i.y)[1] = 80;
				src_magic.at<Vec4b>(i.x, i.y)[2] = 80;
			} else {
				src_magic.at<Vec3b>(i.x, i.y)[0] = 80;
				src_magic.at<Vec3b>(i.x, i.y)[1] = 80;
				src_magic.at<Vec3b>(i.x, i.y)[2] = 80;
			}
			
		} else {
			num = 0;
			if (chann == 4) {
				src_magic.at<Vec4b>(i.x, i.y)[0] = 160;
				src_magic.at<Vec4b>(i.x, i.y)[1] = 160;
				src_magic.at<Vec4b>(i.x, i.y)[2] = 160;
			} else {
				src_magic.at<Vec3b>(i.x, i.y)[0] = 160;
				src_magic.at<Vec3b>(i.x, i.y)[1] = 160;
				src_magic.at<Vec3b>(i.x, i.y)[2] = 160;
			}
		}

	}
	if(f == 1) ROIArea.clear();

	imshow("魔棒", src_magic);
	return;
}



void OnMouse(int event, int x, int y, int flags, void*) {
	if (event == EVENT_LBUTTONDOWN) {
		//需要注意的是，窗口横轴为X轴，竖轴为Y轴，坐标是(x, y)，而矩阵坐标是按照(row, col)，故窗口中的点(x, y)对应的值在矩阵中为(y, x)。
		if (y >= 0 && x >= 0 && y < src.rows && x < src.cols) MagicWandTool(y, x);
	}
}

int main() {
	
	cout << "欢迎使用魔棒工具" << endl;
	cout << "本工具类似Ps的魔棒 可以选取类似区域" << endl;
	cout << "本魔棒工具需要配合1.1.2版本以上的图片RGB化使用" << endl;
	cout << "输入路径或拖动图片到此" << endl;
	getline(cin, filePath);
	if (filePath[0] == '"') filePath = filePath.substr(1, filePath.length() - 2);
	temp = getFileName(filePath);
	replace(temp.begin(), temp.end(), '.', '_');
	temp += ".ncc";
	fstream outfile;
	outfile.open(temp, ios::out | ios::app);
	outfile << filePath << endl;
	src = imread(filePath, -1);
	chann = src.channels();
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	cout << "输入魔棒阈值 当其他点的灰度值与选定点的灰度值的差的绝对值大于阈值时忽略 默认15" << endl;
	cout << "通俗来说就是魔棒阈值越大选取的范围越大" << endl;
	cin >> MagicThreshold;
	cout << "输入1 选择单次选取模式" << endl;
	cout << "输入2 选择多次选取模式" << endl;
	cin >> f;
	cout << endl << "左键点击进行选取" << endl;
	cout << "在选取魔棒区域时程序会生成配置文件" << endl;
	cout << "在确定魔棒区域后将焦点放于图像窗口上按任意键退出" << endl;
	cout << "可在本程序文件夹下找到配置文件" << endl;

	imshow("魔棒", src);
	setMouseCallback("魔棒", OnMouse);
	
	waitKey(0);
	
	outfile << "-1";
	outfile.close();
	time_t now = time(NULL);
	str = temp.substr(0, temp.length() - 4);
	str += '_';
	str += to_string(now);
	str += ".ncc";
	char c = rename(temp.c_str(), str.c_str());
	cout << "完成！！！按任意键退出" << endl;
	return 0;
}