#include < iostream>
using namespace std;
#include<math.h>

const double p1 = 7800;  //小球密度g/cm-3
const double g = 9.78;    //重力加速度
const double p0 = 950;  //蓖麻油密度
const double D = 0.02;  //圆管内径直径
const double t = 0.2;   //时间的不确定度 s
const double drop_L = 25.0;//小球下落经过的距离


int main() {
	//小球直径测量数据
	double length[5][2] = {
		{16.528,15.540},
		{16.547,15.547},
		{16.534,15.545},
		{16.535,15.560},
		{16.547,15.571}
	};
	double temp = 54;//温度
	double drop_time = 6.31;//下落时间
	int i = 0, j = 0;
	double k = 0;

	for (; i < 5; i++) {
		k = k + length[i][0] - length[i][1];
	}
	cout << "小球直径"<<k/5.0 <<"mm" << endl;
	double d = k / 5.0;
	double a = 0, b = 0;
	a = (p1 - p0) * g *drop_time* d * d;
	b = 18 * drop_L * (1 + 2.4 * (d / D));
	
	double n = a / (100. * b);
	cout<<"液体粘度"<<n<<"Pa.s" << endl;

	//不确定度计算
	//时间A类不确定度
	double u_t = t / (double)sqrt(3);
	cout << "时间的A类不确定度" << u_t <<"s" << endl;
	//小球直径不确定度
	double u_l_a = 0.01 / (double)sqrt(3);
	cout << "小球直径的A类不确定度" << u_l_a << "mm" << endl;
	double u_l_b = 0;
	k = 0;
	for (i=0; i < 5; i++) {
		k = k +( (length[i][0] - length[i][1]-d)* (length[i][0] - length[i][1] - d));
	}
	u_l_b = sqrt(k/20.0);
	cout << "小球直径的B类不确定度" << u_l_b << "mm" << endl;
	double u_l = sqrt((u_l_a*u_l_a)+(u_l_b*u_l_b));
	cout << "小球直径的不确定度" << u_l << "mm" << endl;

	double E = 0;
	double temp1 = (2.0/d-(2.4/(D+2.4*d))) * (2.0 / d - (2.4 / (D + 2.4 * d)));
	double temp2 = u_l * u_l;
	double temp3 = (1.0 / drop_time) * (1.0 / drop_time);
	double temp4 = u_t * u_t;

	E = sqrt(temp1*temp2+temp3*temp4);
	cout << "液体粘度的相对不确定度：" <<E << "百分比" << endl;

	double u_n = E * n;
	cout << "液体温度:" << temp << endl;
	cout << "液体粘度的不确定度：" << u_n << "Pa.s" << endl;
}

