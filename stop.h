#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include<assert.h>
#include <queue>
using namespace std;

typedef int VertType;    //顶点数据类型
typedef int InfoType;       //边权数据类型
const int MAXNUM = 501;              //最大站点数
const int VEXNUM = 228;              //顶点数
const int ARCNUM = 300;             //边数
#define INF 1000000
const int control = 100;
struct Station {
    
    int line[3];
    string sta_name;
    int num;

    friend ostream &operator << (ostream &out,struct Station & station)
    {
        out   << "   " << station.sta_name;
        return out;
    }
};

static Station sta[VEXNUM] = {
    {{0}," ",0},
    { {1}, "罗湖",1},
    {{1},"国贸",	2},
    { {1,3},"老街",	3},
    {{1,2},"大剧院",	4},
    {{1,6},"科学馆",5},
    {{1},"华强路",6},
    {{1,10},"岗厦",7},
    {{1,4},"会展中心",8},
    {{1,3},"购物公园",9},
    {{1}	,"香蜜湖",10},
    {{1,7,9},"车公庙",11},
    {{1},"竹子林	",12},
    {{1},"侨城东",13},
    {{1},"华侨城	",14},
    {{1,2},"世界之窗	",15},
    {{1},"白石洲",16},
    {{1},"高新园",17},
    {{1},"深大",18},
    {{1},"桃园",19},
    {{1},"大新",20},
    {{1},"鲤鱼门",21},
    {{1,5},"前海湾",	22},
    {{1},"新安	",23},
    {{1,5},"宝安中心",24},
    {{1},"宝体",25},
    {{1}, "坪洲", 26},
    {{1},"西乡",27},
    {{1},"固戍",28},
    {{1},"后瑞",29},
    {{1},"机场东",30},
    {{2,5},"赤湾",31},
    {{2},"蛇口港",32},
    {{2},"海上世界",33},
    {{2},"水湾",34},
    {{2},"东角头	",35},
    {{2},	"湾厦",	36} ,
    {{2},	"海月"	,37},
    {{2},	"登良",	38},
    {{2},	"后海",	39},
    {{2},	"科苑",	40},
    {{2},	"红树湾",	41},
    {{2}, "侨城北",	42},
    {{2},	"深康",	43},
    {{2,7},	"安托山",	44},
    {{2},	"侨香",	45},
    {{2},	"香蜜",	46},
    {{2},	"香梅北",	47},
    {{2,9},	"景田",	48},
    {{2},	"莲花西",	49},
    {{2,3},	"福田",	50},
    {{2,4},	"市民中心",	51},
    {{2,10},	"岗厦北",	52},
    {{2,7},	"华强北",	53},
    {{2},	"燕南",	54},
    {{2},	"湖贝",	55},
    {{2,5},	"黄贝岭",	56},
    {{2},	"新秀",	57},
    {{2},	"莲塘口岸",	58},
    {{2},	"仙湖路",	59},
    {{2,8},	"莲塘",	60},
    {{3},	"福保",	61},
    {{3},	"益田",	62},
    {{3,7}, "石厦",	63},
    {{3,4},	"少年宫",	64},
    {{3,10},	"莲花村",	65},
    {{3,7},	"华新",	66},
    {{3,6},	"通新岭",	67},
    {{3,9},	"红岭",	68},
    {{3},	"晒布",	69},
    {{3},	"翠竹",	70},
    {{3,7},	"田贝",	71},
    {{3},	"水贝",	72},
    {{3},	"草埔",	73},
    {{3,5},	"布吉",	74},
    {{3},	"木棉湾",	75},
    {{3},	"大芬",	76},
    {{3},	"丹竹头",	77},
    {{3},	"六约",	78},
    {{3},	"塘坑",	79},
    {{3},	"横岗",	80},
    {{3},	"永湖",	81},
    {{3},	"荷坳",	82},
    {{3},	"大运",	83},
    {{3},	"爱联",	84},
    {{3},	"吉祥",	85},
    {{3},	"龙城广场",	86},
    {{3},	"南联",	87},
    {{3},	"双龙",	88},
    {{4,10},	"福田口岸",	89},
    {{4,7,10},	"福民",	90},
    {{4},	"莲花北",	91},
    {{4,9},	"上梅林",	92},
    {{4}, "民乐",	93},
    {{4},	"白石龙",94},
    {{4,5,6},	"深圳北站",	95},
    {{4,6},	"红山",	96},
    {{4}, "上塘",	97},
    {{4},	"龙胜",	98},
    {{4},	"龙华",	99},
    {{4},	"清湖",	100},
    {{4},	"清湖北",	101},
    {{4},	"竹村",	102 },
    {{4},	"茜坑",	103 },
    {{4},	"长湖",	104 },
    { {4},	"观澜",	105 },
    {{4},	"松元厦",	106},
    {{4},	"观澜湖",	107},
    {{4},	"牛湖",	108},
        {{5},	"荔湾",	109},
        {{5},	"铁路公园",	110},
        {{5},	"妈湾",	111},
        {{5},	"前湾公园",	112},
        {{5,9},	"前湾",	113},
        {{5},	"桂湾",	114},
        {{5},	"临海",	115},
        {{5},	"宝华",	116},
        {{5},	"翻身",	117},
        {{5,},	"灵芝",	118},
        {{5},	"洪浪北",	119},
        {{5},	"兴东",	120},
        {{5},	"留仙洞",	121},
        {{5,7},	"西丽",	122},
        {{5},	"大学城",	123},
        {{5},	"塘朗",	124},
        {{5},	"长岭陂",	125},
        {{5},	"民治",	126},
        {{5,10},	"五和",	127},
        {{5},	"坂田",	128},
        {{5},	"杨美",	129},
        {{5},	"上水径",	130},
        {{5},	"下水径",	131},
        {{5},	"长龙",	132},
        {{5},	"百鸽笼",	133},
        {{5},	"布心",	134},
        {{5,7},	"太安",	135},
        {{5},	"怡景",	136},
    { {6},	"体育中心",	137 },
    { {6,7},	"八卦岭",	138 },
    { {6,9},	"银湖",	139 },
    { {6},	"翰岭",	140 },
    { {6},	"梅林关",	141 },
    { {6},	"上芬",	142 },
    { {6},	"元芬",	143 },
    { {6},	"阳台山东",	144 },
    { {6},	"官田",	145 },
    { {6}	,"上屋",	146 },
    { {6},	"长圳",	147 },
    { {6},	"凤凰城",	148 },
    { {6},	"光明大街",	149 },
    { {6,61},	"光明",	150 },
    { {6},	"科学公园",	151 },
    { {6},	"楼村",	152 },
    { {6},	"红花山",	153 },
    { {6},	"公明广场",	154 },
    { {6},	"合水口",	155 },
    { {6},	"薯田埔",	156 },
    { {6},	"松岗公园",	157 },
    { {6},	"溪头",	158 },
    { {6},	"松岗",	159 },
    { {61},	"圳美",	160 },
    { {61},	"中大",	161 },
    { {61},	"深理工",	162 },
    { {7},	"西丽湖",	163 },
    { {7},	"茶光",	164 },
    { {7},	"珠光",	165 },
    { {7},	"龙井",	166 },
    { {7},	"桃源村",	167 },
    { {7},	"深云",	168 },
    { {7},	"农林",	169 },
    { {7},	"上沙",	170 },
    { {7},	"沙尾",	171 },
    { {7},	"皇岗村",	172 },
    { {7},	"皇岗口岸",	173 },
    { {7},	"赤尾",	174 },
    { {7},	"华强南",	175 },
    { {7},	"黄木岗",	176 },
    { {7,9},	"红岭北",	177 },
    { {7},	"笋岗",	178 },
    { {7},	"洪湖",	179 },
    { {8},	"梧桐山南",	180 },
    { {8},	"沙头角",	181 },
    { {8},	"海山",	182 },
    { {8},	"盐田港西",	183 },
    { {8},	"深外高中",	184 },
    { {8},	"盐田路",	185 },
    { {9},	"梦海",	186 },
    { {9},	"怡海",	187 },
    { {9},	"荔林",	188 },
    { {9},	"南油西",	189 },
    { {9}, "南油",	190 },
    { {9},	"南山书城",	191 },
    { {9},	"深大南",	192 },
    { {9},	"粤海门",	193 },
    { {9},	"高新南",	194 },
    { {9},	"红树湾南",	195 },
    { {9},	"深湾",	196 },
    { {9},	"深圳湾公园",	197 },
    { {9},	"下沙",	198 },
    { {9},	"香梅",	199 },
    { {9},	"梅景",	200 },
    { {9},	"下梅林",	201 },
    { {9},	"梅村",	202 },
    { {9,10},	"孖岭",	203 },
    { {9},	"泥岗",	204 },
    { {9},	"园岭",	205 },
    { {9},	"红岭南",	206 },
    { {9},	"鹿丹村",	207 },
    { {9},	"人民南",	208 },
    { {9},	"向西村",	209 },
    { {9},	"文锦",	210 },
    { {10}, "冬瓜岭",	211 },
    { {10},	"雅宝",	212 },
    { {10},	"南坑",	213 },
    { {10},	"光雅园",	214 },
    { {10},	"坂田北",	215 },
    { {10},	"贝尔路",	216 },
    { {10},	"华为",	217 },
    { {10},	"岗头",	218 },
    { {10},	"雪象",	219 },
    { {10},	"甘坑",	220 },
    { {10},	"凉帽山",	221 },
    { {10},	"上李朗",	222 },
    { {10},	"木古",	223 },
    { {10},	"华南城",	224 },
    { {10},	"禾花",	225 },
    { {10},	"平湖",	226 },
    { {10},	"双拥街",	227 }
 
};

//站点 string 判断序号
inline int num_judge(string name) {

    int i = 0,flag=0;
    for (; i < VEXNUM && flag == 0; i++) {
        if (name == sta[i].sta_name) {
            flag = 1;
        }
    }
        return i - 1;

}

//地图显示
inline void map_show() {
    int i = 0;
    Station* s=NULL;
    for (i = 1; i < VEXNUM; i++) {
        s = &sta[i];
        cout << *s << endl;
    }
}

//数据显示
inline void show_data(int a) {
    Station* s = NULL;
    s = &sta[a];
    cout << *s<<endl ;
}

//打印线路
inline void print_route(int a, int b) {
    Station* s1 = NULL;
    s1 = &sta[a];
    Station* s2 = NULL;
    s2 = &sta[b];
    cout << "已选择的站点是从：" << *s1 << "\t到\t" <<* s2 << endl;
}

//线路判断函数
inline int line_choose(int sta1,int sta2) {
    int i = 0, j = 0,flag=0;
    int line = 0;
    for (i=0; i < 3&& sta[sta1].line[i]!=0&&flag==0; i++) {
        for (j=0; j < 3&& sta[sta2].line[j]!=0&&flag==0; j++) {
            if (sta[sta1].line[i] == sta[sta2].line[j]) {
                line = sta[sta1].line[i];
                flag = 1;
            }
        } 
    }
    return line;
}

//结构体：边节点
 struct ArcNode {
public:
	int adjVex;                    //边指向的边节点位置
	InfoType value;            //边的权值
	 ArcNode *next;   //指向下一各边结点信息
};
//结构体：表示中的顶点节点,无向图
struct VNode {
	VertType data;          //顶点的信息(标号)
	ArcNode * first;         //顶点的第一条边，指针
};


 //邻接表
typedef struct ALGRAPH {
	VNode vexs[MAXNUM];     //顶点的数组
	int vexNum, arcNum;            //图的顶点数和边数
}ALGRAPH; 


//顶点节点，保存id和到源顶点的估算距离，优先队列需要的类型
struct Node
{
	int id;     //从源到目标顶点id
	int w;      //从源到id的距离
    int tran;

	//因要实现最小堆，按升序排列，因而需要重载运算符，重定义优先级，使得结点升序
    friend bool operator < (struct Node a, struct Node b)
    {
        if (a.tran < b.tran) {
            return true;
        }
        else if (a.tran == b.tran) {
            return a.w > b.w;
        }
        else {
            return false;
        }
    }
};


extern ALGRAPH* graph ;    //指向图的指针
extern ALGRAPH g;   //连接表对象
extern int path[MAXNUM];    //路径
extern int visited[MAXNUM] ;    //已访问节点
int transfers[MAXNUM];
extern Node dist[MAXNUM];
 int line[MAXNUM];   //记录当前经过站点属于哪条线路

extern priority_queue<Node>q;    //利用堆优化最小权值边的时间复杂度//默认最大堆

 inline void Dijkstra(ALGRAPH &g,int v0) {
    int i=0;
    int j=0, k=0;
    for (i = 0; i < MAXNUM; i++) {  
        dist[i].id = i;
        dist[i].w = INF;
        dist[i].tran = INF;
    //初始化Dijkstra表格
        path[i] = -1;
        visited[i] = 0;
        transfers[i] = 0;
        line[i] = 0;
    }
  

    dist[v0].w = 0;
    dist[v0].tran = 0;
    q.push(dist[v0]);       //将源点入优先队列
    //int line = 0;//地铁线路


    while (!q.empty())
    {
        Node node = q.top();  //取得当前权值w最小值对应的结点
        q.pop();
        int u = node.id;
        int temp_line = 0;
        if (visited[u])     //若当前结点还没有访问过
            continue;
        visited[u] = 1;
       
        ArcNode* p = g.vexs[u].first;    //取得当前结点对应的第一条边
      
                  while (p)
        {
            int temp_v = p->adjVex;
            int temp_w = p->value;
            int temp_trans = 0;
            int flag = 0;

            if (u == v0) {
                       for (j = 0; j < 5 && flag == 0; j++) {
                            line[u] = sta[u].line[j];
                            for (k = 0; k < 5 && flag == 0; k++) {
                                if (sta[p->adjVex].line[k] == line[u]) {
                                    flag = 1;
                                    line[temp_v] = line[u];
                                }
                            }
                        }
           }
            else {
                for (k = 0; k < 5 && flag == 0; k++) {
                    if (sta[p->adjVex].line[k] == line[u]) {
                        flag = 1;
                        line[temp_v] = line[u];
                    }
                        }
                if (flag == 0) {//说明要换乘，找到当前u和temp_v共同线路
                    for (j = 0; j < 3 && flag == 0; j++) {
                        temp_line = sta[u].line[j];
                        for (k = 0; k < 3 && flag == 0; k++) {
                            if (sta[p->adjVex].line[k] == temp_line) {
                                flag = 1;
                                line[temp_v] = temp_line;
                            }
                        }            
                    }
                    flag = 0;
                }
            }
                        if (flag) {
                            temp_trans = 0;
                        }
                        else {
                            temp_trans = 1;
                            temp_w += control;
                        }
           
            //若该边对应的另外一个结点还没有访问过并且源点到u加上u到 temp_v的权值小于源点直接到 temp_v的权值且换乘次数最少，更新权值
            if (!visited[temp_v] &&dist[temp_v].w>dist[u].w+temp_w&& dist[temp_v].tran > dist[u].tran + temp_trans)
            {
                    
                    dist[temp_v].w = dist[u].w + temp_w;
                    dist[temp_v].tran = dist[u].tran + transfers[temp_v];
                    path[temp_v] = u;        // 更新源点到 temp_v的最短路径的 temp_v前一结点为u
                    transfers[temp_v] = temp_trans;//更新temp_v处的换乘信息
                    q.push(dist[temp_v]);
                }
                p = p->next;    

        }
    }
   
}

 void CreatGraph() {
   
    graph = (ALGRAPH*)malloc(sizeof(ALGRAPH));   //申请内存 
    graph = &g;
    if (graph == NULL) {
        return;
    }
    graph->vexNum = VEXNUM;     //图的顶点数
    graph->arcNum = ARCNUM;     //图的边数

    //初始化顶点的指针，以免出现非法访问
    int i = 0;
    for (i = 0; i < graph->vexNum; i++) {
        graph->vexs[i].data = i;
        graph->vexs[i].first = NULL;
    }

    ifstream fp;
    int source=0;
    int n=0, w=0;
    fp.open("subway_data.txt", ios::in);
    if (!fp.is_open()) {
        cout << "打开文件失败！！" << endl;
        return;
    }
    string line;
    int count = 0;

    while (1)
    {

        fp >> source;

        if (!getline(fp, line)) break;
        stringstream ss(line); // 读取一行文件，将其当作输入流输入
        string token;

        while (ss >> token)
        {
            n = stoi(token);
            if (ss >> token) {
                w = stoi(token);
            }

            ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
            assert(q);
            q->adjVex = n;
            q->value = w;

            q->next = g.vexs[source].first;
            g.vexs[source].first = q;


        }
    }

    fp.close();

}

