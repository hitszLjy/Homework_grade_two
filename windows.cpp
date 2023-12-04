#include <iostream>
#include "head.h"
#include <conio.h>
#include<windows.h>
#include <string>
#include "stop.h"
using namespace std;

 ALGRAPH* graph;    //指向图的指针
 ALGRAPH g;   //连接表对象
 int path[MAXNUM];
 int visited[MAXNUM];
 Node dist[MAXNUM];
 priority_queue<Node>q;    //利用堆优化最小权值边的时间复杂度

 int main() {

	 CreatGraph();//创建连接表
	 welcome();
	 Sleep(1 * 1000);
	 main_menu();


	 return 0;
 }


void welcome() {

	cout << "\t欢迎进入地铁自助售票系统！\t" << endl;
	cout << "\t作者信息 ：hyq/ljy" << endl;
	cout << "\t版权信息：" << endl;

}

int main_menu() {

	char select;

	//显示出主菜单以及三个可选项
	cout << "主菜单" << endl;
	cout << "购票（请按1键）" << endl;         //键盘1代表购票
	cout << "地图查询（请按2键）" << endl;  //2代表查询地图
	cout << "退出系统（请按ESC键）" << endl; //其中Esc（ASCII27）代表退出系统

	while (select = _getch()) {
		if (select == '1') {
			inform();
		}
		else if (select == '2') {
			map();
		}
		else if (select == 27) {
			cout << "感谢使用，祝您旅途愉快!" << endl;
			exit(0);
		}
	}

	return 0;
}

//用户使用系统须知函数
int inform() {
	char select;

	cout << "《用户须知》" << endl;
	cout << "请在阅读了购票用户须知后按下ENTER键进行确认" << endl;

	//用 while 循环控制键盘的输入来确定用户购票须知

	while (select = _getch()) {
		if (select == 13) {
			purchase();
			break;
		}
	}
	return 0;
}

//购票程序
int purchase() {
	char ch;
	int start = 0;
	int finish = 0;
	string start_n;
	string finish_n;
	int num = 0;
	int price = 0;
	cout << "购票程序" << endl;

	cout << "请选择始发站：（或按下ESC键返回主界面）" << endl;
	map_show();

	cin >> start_n;
	start =  num_judge(start_n);
	cout << "请选择终点站：(或按下ESC键返回主界面）" << endl;
	map_show();
	
	cin >> finish_n;
	finish = num_judge(finish_n);
	price = calculate(start, finish);
	cout << "单张票价：" << price << endl;
	do {
		cout << "请输入所需购买的车票张数：" << endl;       //无法识别非法字符
		cin >> num;
	} while (num < 0);

	cout << "总票价是：" << price * num << endl;
	print_route(start , finish );
	cout << "请选择是否购买此种车票，数量为：" << num << "（ENTER键表示确定，ESC键表示退回购票界面）" << endl;
	while (ch = _getch()) {
		if (ch == 13) {
			pay(price * num);
			break;
		}
		else if (ch == 27) {
			main_menu();
			break;
		}
	}


	return 0;
}

//显示地图函数，学习用类封装地图的全部显示、部分显示、查询等功能
int map() {
	char select;
	cout << "此处显示地图（按下ESC键后返回主菜单，按下1键后跳转购票窗口）" << endl;
	map_show();
	while (select = _getch()) {
		if (select == '1') {
			purchase();
			break;
		}
		else if (select == 27) {
			main_menu();
			break;
		}
	}
	return 0;
}

int calculate(int a, int b) {
	
	Dijkstra(g, b);   //图与源点
	int temp = a;
	int trans_count = 0;//换乘次数
	int length = 0;
	int line_f = 0;
	int line_s = 0;
	Station* s = NULL;
	line_f = line_choose(temp, path[temp]);
	if (dist[b].w != INF) {
		
		cout  << a << sta[a].sta_name << "到" << b << sta[b].sta_name << "的推荐乘车路径为：" << endl;
		cout << "开始：";
		cout << line_f << "号线";
		show_data(temp);   
		
		
		while (path[temp] != -1) {	
			cout << " | " ;
			cout << line_f << "号线";
			//show_data(path[temp]);  
			
			s = &sta[path[temp]];
			cout << *s << endl;
			//打印该站点的信息
			if (transfers[temp] == 1) {
			
				line_s = line_choose(path[temp], path[path[temp]]);
				cout  << "—————— 在此站点由"<<line_f<<"号线换乘" ;
				cout << line_s << "号线" <<endl;
				trans_count++;
				line_f = line_s;
			}

			temp = path[temp];
		}
		cout << "结束" << endl;
		length = dist[a].w - control * trans_count;
		cout << endl;
		cout  << "总的最短路径长度为：" << length<< endl;
		cout << "换乘次数为："  <<trans_count<< endl;
	}
	else {
		cout << "源点" << a << sta[a].sta_name << "到" << b << sta[b].sta_name << "没有路径" << endl;
		length = -1;//防止费用
	}
	cout << endl;

	if (length >= 0 && length <= 4) {
		return 2;
	}
	else if (length > 4 && length <= 8) {
		return 3;
	}
	else if (length > 8 && length <= 12) {
		return 4;
	}
	else if (length > 12 && length <= 18) {
		return 5;
	}
	else if (length > 18 && length <= 24) {
		return 6;
	}
	else if (length > 24 && length < 100) {
		return (6 + (1 + (length - 24) / 8));
	}
	else if (length == INF) {
		return 0;
	}
	else return 0;

}

//投币找币流程，question：解决ESC返回主界面问题
int pay(int price) {
	bool flag = 0;
	int select = 0;
	float money = 0;
	cout << "支付界面" << endl;
	cout << "请选择支付方式：1、现金  2、支付宝3、微信" << endl;
	cin >> select;
	if (select == 1) {
		cout << "现金支付界面" << endl;
		cout << "需支付现金：" << price << "元" << endl;

		while (flag == 0) {
			cout << "请将纸币或硬币放入验钞口，系统将自动识别（ESC键取消支付并返回主菜单）" << endl;
			cin >> money;
			if (money < price) {
				cout << "现金不足，支付失败！退回现金，请重新放入。" << endl;
			}
			else {
				cout << "找零 : " << money - price << endl;
				flag = 1;
			}
		}
	}
	else if (select == 2) {
		cout << "支付宝支付界面" << endl;
		cout << "请扫描图中二维码支付（ESC键取消支付并返回主菜单）" << endl;
		cout << "二维码图片显示" << endl;
		Sleep(5 * 1000);
	}
	else if (select == 3) {
		cout << "微信支付界面" << endl;
		cout << "请扫描图中二维码支付（ESC键取消支付并返回主菜单）" << endl;
		cout << "二维码图片显示" << endl;
		Sleep(5 * 1000);
	}

	cout << "支付成功，请拿好您的车票，祝您旅途愉快！" << endl;

	return 0;
}
