// Bitmap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

typedef struct Bitmap {
	char fileName;//占有此块的文件名
	bool occupied = false;//是否空闲，初值都为
}Bitmap;

Bitmap(*bitmap)[8] = new Bitmap[8][8];

//计算空闲块数
int getFreeNum(int fileLen) {
	int freeNum = 0;//空闲块数
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (!bitmap[i][j].occupied)
				freeNum++;
	return freeNum;
}

//申请内存
void memReq() {
	char fileName;
	int fileLen;
	cout << "请输入创建的文件名：";
	cin >> fileName;
	cout << "请输入需要的磁盘块数(不得超过最大数64)：";
	cin >> fileLen;
	//判断能否分配
	if (fileLen > getFreeNum(fileLen))
		cout << "所需磁盘块数过大，分配失败！" << endl;
	else 
	{
		cout << "分配的物理地址：" << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!bitmap[i][j].occupied) {
					bitmap[i][j].occupied = true;
					bitmap[i][j].fileName = fileName;
					fileLen--;
					cout << "柱面号：" << i << "\t磁道号：" << j / 4 << "\t物理记录号：" << j % 4 << endl;
				}
				if (fileLen <= 0) {
					return;
				}
			}
		}
	}
}

//释放空间
bool memFree() {
	char fileName;
	cout << "请输入释放空间的文件名：";
	cin >> fileName;
	cout << "回收时的字节号和位数: " << endl;
	bool isFind = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (bitmap[i][j].fileName == fileName) {
				isFind = true;
				bitmap[i][j].occupied = false;
				bitmap[i][j].fileName = ' ';
				cout << "字节号" << i << "\t位数" << j << endl;
			}

		}
	}
	if (!isFind) {
		cout << "未找到文件!" << endl;
	}
	return isFind;
}

//打印位示图
void showBitmap() {
	cout << "-----------------------磁盘存储位示图---------------------" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (bitmap[i][j].occupied) {
				cout << "1\t";
			}
			else {
				cout << "0\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	while (true) {
		int command;
		cout << "选择功能：[1]查看位示图；[2]空间申请；[3]空间回收；[4]退出" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			showBitmap();
			break;
		case 2:
			memReq();
			break;
		case 3:
			memFree();
			break;
		case 4:
			break;
		default:
			break;
		}
	}
	return 0;
}

