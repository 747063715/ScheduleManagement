/*
数据结构课程设计
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <sstream>                        //调用istringstream需包含
using namespace std;
#define OK true
#define ERROR false
#define Status bool
#define maxn 10010
typedef struct schedule_information
{
    string time;                          //日期用字符串类型表示，方便后面调用字符串函数
    char place[100];                      //地点数组
    char event[100];                      //事件数组
    char if_finish[2];                    //判断是否完成，数组里有两个字符：是，否
} Schedule;

//单链表的储存结构
typedef struct SLNode
{
    Schedule data;                          //数据域，是一个结构体类型
    //struct SLNode *prior;                 //前去指针
    struct SLNode *next;                    //后继指针

} SLNode, *SLinkList;
int length;
//单链表初始化
Status InitList(SLinkList &L)
{
    L = new SLNode;
    L->next = NULL;
    return true;
}
//获取当前时间字符串
string GetNowTime()
{
  time_t setTime;
  time(&setTime);
  tm *ptm = localtime(&setTime);
  string time = std::to_string(ptm->tm_year + 1900) + "-" + std::to_string(ptm->tm_mon + 1) + "-" + std::to_string(ptm->tm_mday);
  return time;
}

//判断是否为闰年
Status is_leap_year(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) //判断闰年计算方法
		return OK;
	else
		return ERROR;
}

//字符串转int
int stringToInt(string str)
{
    int result;
    istringstream is(str);
    is >> result;
    return result;
}
//判断时间满足yyyy-mm-dd
bool CheckTime(string time)
{
    //判断是否是10位数
    string s;
    bool judge = false;
    if (time.length() != 10)
    {
        return judge;
    }
    //判断第5位和第8位是否是"-"
    static int dash[2] = {4, 7};
    for (int i = 0; i < 2; ++i)
    {
        if (time[dash[i]] != '-')
        {
            return judge;
        }
    }
    /*符合年>2019*/
    int i;
    for (i = 0; i < 4; i++)
        s += time[i];
    int year = stringToInt(s);
    if (year < 2019)
        return judge;
    /*符合01<=月<=12*/
    s = ""; //置空
    s += time[5];
    s += time[6];
    int month = stringToInt(s);
    if (month < 1 || month > 12)
        return judge;
    /*符合01<=日<=31*/
    s = ""; //置空
    s += time[8];
    s += time[9];
    int day = stringToInt(s);
    if (day < 1 || day > 31)
        return judge;
    judge = true;
    return judge; //日期符合yyyy-mm-dd
}

//给定一个年月日，计算这一年已经过的天数
int total_day(string s)
{
    //把年，月，日从字符串中提取出来，并转化成整型数
    int i;
    string s1;
    for (i = 0; i < 4; i++)
    {
        s1 += s[i];
    }
    int year1 = stringToInt(s1);
    /*月*/
    s1 = ""; //置空
    s1 += s[5];
    s1 += s[6];
    int month1 = stringToInt(s1);
    /*日*/
    s1 = ""; //置空
    s1 += s[8];
    s1 += s[9];
    int day1 = stringToInt(s1);
    int sum = 0;
    switch (month1)
    {
    case 1:
    {
        return sum =  day1;
    }
    case 2:
        sum = 31 + day1;
        break;
    case 3:
        sum = 59 + day1;
        break;
    case 4:
        sum = 90 + day1;
        break;
    case 5:
        sum = 120 + day1;
        break;
    case 6:
        sum = 151 + day1;
        break;
    case 7:
        sum = 181 + day1;
        break;
    case 8:
        sum = 212 + day1;
        break;
    case 9:
        sum = 243 + day1;
        break;
    case 10:
        sum = 273 + day1;
        break;
    case 11:
        sum = 304 + day1;
        break;
    case 12:
        sum = 334 + day1;
        break;
    default:
        cout<<"输入的月份有错误\n"<<endl;
        break;
    }
    if (month1 > 2)
    {
        if (((year1 % 4 == 0) && (year1 % 100 != 0)) || (year1 % 400) == 0)
        {
            sum = sum + 1;
        }
    }
    return sum;
}
//年与年相差的天数
int total_year_day(string time1, string time2)
{
    //把年，月，日从字符串中提取出来，并转化成整型数
    int i;
    string s1, s2;
    for (i = 0; i < 4; i++)
    {
        s1 += time1[i];
        s2 += time2[i];
    }
    int year1 = stringToInt(s1);
    int year2 = stringToInt(s2);
    /*月*/
    s1 = ""; //置空
    s2 = ""; //置空
    s1 += time1[5];
    s1 += time1[6];
    s2 += time2[5];
    s2 += time2[6];
    int month1 = stringToInt(s1);
    int month2 = stringToInt(s2);
    /*日*/
    s1 = ""; //置空
    s2 = ""; //置空
    s1 += time1[8];
    s1 += time1[9];
    s2 += time2[8];
    s2 += time2[9];
    int day1 = stringToInt(s1);
    int day2 = stringToInt(s2);
    int sum_year_day = 0;
    int j = 0;
    sum_year_day = (year2 - year1) * 365;
    for (j= year1; j < year2; j++)
    {
        if (((j % 4 == 0) && (j % 100 != 0)) || (j % 400) == 0)
        {
            sum_year_day = sum_year_day + 1;
        }
    }
    return sum_year_day;
}

//创建单链表,从文件读取数据
void CreateList_R(SLinkList &L, int n) 
{                                                //算法2.12 后插法创建单链表正位序输入n个元素的值，建立带表头结点的单链表L
	SLinkList p, r;
	L = new SLNode;
	L->next = NULL;                                                                     //先建立一个带头结点的空链表
	r = L;                                                                              //尾指针r指向头结点
	length = 0;
	fstream file;                                                                       //打开文件进行读写操作
	file.open("book.txt");
	if (!file) {
		cout << "未找到相关文件，无法打开！" << endl;
		exit(ERROR);
	}
    while (!file.eof()) {                                                              //将文件中的信息运用后插法插入到链表中
        file.get();
        if (file.peek() == '\n')                                                       //判断文件是否结束
        {
            break;
        }
        p = new SLNode;//生成新结点 
        file >> p->data.time >> p->data.place >> p->data.event >> p->data.if_finish;   //输入元素值赋给新结点*p的数据域
        p->next = NULL;
		r->next = p;                                                                   //将新结点*p插入尾结点*r之后 		
		r = p;                                                                         //r指向新的尾结点*p
		length++;                                                                      //同时对链表长度进行统计
	}
	file.close();                                                                      //关闭文件
}

//求单链表的表长
int ListLength(SLinkList L)
{
    SLinkList p;
    p = L->next;
    int i = 0;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}
//按位置查找时间，地点，事件，完成状态
int Search(SLinkList &L, int i)
{
    if (i < 1)
    {
        return 0;
    }
    else
    {
        SLinkList p = L->next;
        int k = 0;
        while (p != NULL && k < i - 1)
        {
            p = p->next;
            k++;
        }
        if (p == NULL)
        {
            cout << "超过表长" << endl;
            return 0;
        }
        cout << i << p->data.time;
    }
    return 1;
}
//确定第i个元素的指针p
SLNode *GetElemP_DuL(SLinkList L, int i)
{
    //在带头结点的双向链表L中查找第i个元素，返回结点的地址
    int j;
    SLinkList p;
    p = L->next;
    j = 1; //初始化，p指向第一个结点，j为计数器
    while (j < i && p)
    { //顺链域向后扫描，直到p指向第i个元素或p为空
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return NULL; //第i个元素不存在
    return p;
}
//删除第i个结点
Status Delete_List(SLinkList &L, int i)
{
	SLinkList p, q;
	int j;
	p = L;                          //p和L开始都指向头结点
	j = 0;
	while ((p->next) && (j < i - 1)) 
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || (j > i - 1))
		return ERROR; 
	q = p->next; 
	p->next = q->next; 
	delete q; 
	--length;
	return OK;
}
//修改第k个元素的时间
Status Modify_time(SLinkList L, int k)
{
    if (k < 1 || k > ListLength(L))
    {
        cout << "位置不合理" << endl;
    }
    int i = 1;
    SLinkList cur = L;
    while (cur != NULL)
    {
        if (i == k)
        {
            cout << "修改的时间：" << endl;
            SLinkList p = GetElemP_DuL(L,k);                 //获取当前结点的指针
            cin >> p->data.time;
        }
        cur = cur->next;
        i++;
    }
    return true;
}

//修改第k个元素的地点
Status Modify_place(SLinkList L, int k)
{
    if (k < 1 || k > ListLength(L))
    {
        cout << "位置不合理" << endl;
    }
    int i = 1;
    SLinkList cur = L;
    while (cur != NULL)
    {
        if (i == k)
        {
            cout << "修改的地点：" << endl;
            SLinkList p = GetElemP_DuL(L,k);                 //获取当前结点的指针
            cin >> p->data.place;
        }
        cur = cur->next;
        i++;
    }
    return true;
}
//修改第k个元素的事件
Status Modify_event(SLinkList L, int k)
{
    if (k < 1 || k > ListLength(L))
    {
        cout << "位置不合理" << endl;
    }
    int i = 1;
    SLinkList cur = L;
    while (cur != NULL)
    {
        if (i == k)
        {
            cout << "修改的事件：" << endl;
            SLinkList p = GetElemP_DuL(L,k);                 //获取当前结点的指针
            cin >> p->data.event;
        }
        cur = cur->next;
        i++;
    }
    return true;
}
//修改第k个元素的事件完成状态
Status Modify_if_finish(SLinkList L, int k)
{
    if (k < 1 || k > ListLength(L))
    {
        cout << "位置不合理" << endl;
    }
    int i = 1;
    SLinkList cur = L;
    while (cur != NULL)
    {
        if (i == k)
        {
            cout << "修改的完成状态：" << endl;
            SLinkList p = GetElemP_DuL(L,k);                 //获取当前结点的指针
            cin >> p->data.if_finish;
        }
        cur = cur->next;
        i++;
    }
    return true;
}
//新增日程安排信息
Status Newly_Add(SLinkList &L, int i, Schedule e)
{
    SLinkList p = L;
    int j = 0;
    while(p && j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!p || j>i)
    {
        cout<<"新增失败"<<endl;
    }
    else
    {
        SLinkList new_LNode = new SLNode;
        new_LNode->data = e;
        new_LNode->next = p->next;
        p->next = new_LNode;
    }
    return OK;
}
//查看日程安排信息
void ShowList(SLinkList &L)
{
    SLinkList p;
    p = L->next;
    if (p == NULL)
    {
        cout << "这是一个空链表！" << endl;
    }
    cout<<left << setw(15)<<"时间"<< "\t" << left << setw(50)<<"地点"<<"\t" << left << setw(5)<<"事件"<<"\t" << left << setw(5)<<"是否完成"<<endl;
    cout<<endl;
    while (p)
    {
        cout << left << setw(15) << p->data.time << "\t" << left << setw(50) << p->data.place << "\t" << left << setw(5) << p->data.event << "\t" << left << setw(5) << p->data.if_finish << endl;
        p = p->next;
    }
}

//信息插入日程安排链表
void InsertList(SLinkList &nowL,Schedule e){
    SLinkList p = nowL;
    SLinkList new_LNode = new SLNode;
    while(p&&p->next&&p->next->next&&p->next->data.time<e.time)                     //按按顺序插入，即按照时间的远近排序
        p=p->next;
    new_LNode->data=e;
    new_LNode->next=p->next;
    p->next=new_LNode;
}
/*
b)查看最近日程安排:显示即将需要完成的日程安排，根据距离今天的时间长短
排序，优先显示最近日程，并提醒倒计时还剩几天，对于时间已经过去但是未
完成的日程需要特别提示，并显示在顶部;
*/

//在单链表中查看近日日程安排
void ShowNow(SLinkList &L)
{
    SLinkList nowL;
    InitList(nowL);
    string nowtime=GetNowTime();    //当前时间
    SLinkList p;
    p = L->next;
	nowL->next = NULL;              //先建立一个带头结点的空链表
    if (p == NULL)
    {
        cout << "空表" << endl;
        return;
    }
    int i=0;
    while (p)
    {
        Schedule e;
        e=p->data;
       // 对于未完成的日程和不小于当天的日程插入nowL链表中
        if(!strcmp(p->data.if_finish,"否")||e.time>=nowtime){
            InsertList(nowL,e);  
            if(i==0){
                InsertList(nowL,e);  
                i++;
            }
        }
        p = p->next;
    }
    nowL=nowL->next;
    cout<<"近日日程安排如下："<<endl;
    cout<<left << setw(15)<<"时间"<< "\t" << left << setw(50)<<"地点"<<"\t" << left << setw(5)<<"事件"<<"\t" << left << setw(5)<<"是否完成"<<endl;
    cout<<endl;
    //输出最近日程安排
    while(nowL){
        cout << left << setw(15) << nowL->data.time << "\t" <<
         left << setw(50) << nowL->data.place << "\t" << left <<
          setw(5) << nowL->data.event << "\t" << left << setw(5) <<
           nowL->data.if_finish << "\t" << left << setw(5);
        int sum=total_year_day(nowtime,nowL->data.time)-total_day(nowtime)+total_day(nowL->data.time);                  //计算两个日期相差多少天
        if(sum>=0)
            cout<<sum<<endl;
        else
            cout<<endl;
        nowL = nowL->next;
        if(nowL->next==NULL)
            break;
    }
}
/*
a)查看历史日程安排:显示过去已完成的日程安排，根据距离今天时间远近排序，
优先显示刚刚完成的日程，其中时间已经过去但是未完成的日程需要特别提
示，并显示在顶部。
*/
//在单链表中查看历史日程安排
void ShowHistory(SLinkList &L)
{
    SLinkList historyL1,historyL2;
    InitList(historyL1);
    InitList(historyL2);
    string nowtime=GetNowTime();         //当前时间
    SLinkList p;
    p = L->next;
	historyL1->next = NULL;              //先建立一个带头结点的空链表
    historyL2->next = NULL;              //先建立一个带头结点的空链表
    if (p == NULL)
    {
        cout << "空表" << endl;
        return;
    }int i=0,j=0;
    while (p)
    {
        Schedule e;
        e=p->data;
        // 对于小于当天且未完成的日程插入historyL1链表中
        if(e.time<nowtime&&!strcmp(e.if_finish,"否")){
            InsertList(historyL1,e); 
            if(i==0){
                InsertList(historyL1,e);
                i++;
            }
        }
               
        // 对于小于当天且完成的日程插入historyL2链表中
        if(e.time<nowtime&&!strcmp(e.if_finish,"是")){
            InsertList(historyL2,e); 
            if(j==0){
                InsertList(historyL2,e); 
                j++;
            }
        }
               
        p = p->next;
    }
    cout<<"历史日程安排如下："<<endl;
    cout<<left << setw(15)<<"时间"<< "\t" << left << setw(50)<<"地点"<<"\t" << left << setw(5)<<"事件"<<"\t" << left << setw(5)<<"是否完成"<<endl;
    //输出历史日程安排
    while(historyL1){
        cout << left << setw(15) << historyL1->data.time << "\t" <<
         left << setw(50) << historyL1->data.place << "\t" << left <<
          setw(5) << historyL1->data.event << "\t" << left << setw(5) <<
           historyL1->data.if_finish << endl;
        historyL1 = historyL1->next;
        if(historyL1->next==NULL)
            break;
    }
    while(historyL2){
        cout << left << setw(15) << historyL2->data.time << "\t" <<
         left << setw(50) << historyL2->data.place << "\t" << left <<
          setw(5) << historyL2->data.event << "\t" << left << setw(5) <<
           historyL2->data.if_finish << endl;
        historyL2 = historyL2->next;
        if(historyL2->next==NULL)
            break;
    }
}

int main()
{
    int n;
    SLinkList L;
    int option = -1;
    //显示欢迎菜单界面，用户根据提示选择所需要的功能
    cout << GetNowTime() << endl;
    cout << "*******欢迎使用日程安排系统*******" << endl;
    cout << " 1----------->初始化单链表" << endl;
    cout << " 2----------->创建单链表" << endl;
    cout << " 3----------->新增日程安排信息" << endl;
    cout << " 4----------->修改日程安排信息的时间" << endl;
    cout << " 5----------->修改日程安排信息的地点" << endl;
    cout << " 6----------->修改日程安排信息的事件" << endl;
    cout << " 7----------->修改日程安排信息的完成状态" << endl;
    cout << " 8----------->删除日程安排信息" << endl;
    cout << " 9----------->查看历史日程安排" << endl;
    cout << " 10---------->查看最近日程安排" << endl;
    cout << " 11---------->打印单链表" << endl;
    cout << " 0---------->退出日程安排系统" << endl;
    cout << "********************************" << endl;
    cout << "请选择需要的功能：" << endl;
    while (option != 0)
    {
        cin >> option;
        switch (option)
        {
        case 1:
        {
            if (InitList(L))
                cout << "初始化成功链表!\n\n";
            break;
        }
        case 2:
        {
            cout << "录入日程信息：时间，地点，事件，是否完成" << endl;
            CreateList_R(L,length);
            cout<<"录入成功！"<<endl;
            break;
        }
        case 3:
        {
            int choose;
            Schedule e;
            cout << "请输入需要新增日程信息的位置和新增日程信息的时间 地点 事件 完成状态：" << endl;
            cin >> choose;
            cin >> e.time >> e.place >> e.event >> e.if_finish;
            if(CheckTime(e.time))
            {
                if (Newly_Add(L, choose, e))
                {
                    cout << "新增日程信息成功！\n\n"
                         << endl;
                }
                else
                {
                    cout << "新增日程信息失败！\n\n"
                         << endl;
                }
            }
            else
            {
                cout<<"时间错误！"<<endl;

            }
            break;
        }
        case 4:
        {
            cout << "请输入需要修改的位置：" << endl;
            int position;
            cin >> position;
            if (Modify_time(L, position))
            {
                cout << "修改成功！\n\n"
                     << endl;
            }
            else
            {
                cout << "修改失败！\n\n"
                     << endl;
            }
            break;
            break;
        }
        case 5:
        {
            cout << "请输入需要修改的位置：" << endl;
            int position;
            cin >> position;
            if (Modify_place(L, position))
            {
                cout << "修改成功！\n\n"
                     << endl;
            }
            else
            {
                cout << "修改失败！\n\n"
                     << endl;
            }
            break;
        }
        case 6:
        {
            cout << "请输入需要修改的位置：" << endl;
            int position;
            cin >> position;
            if (Modify_event(L, position))
            {
                cout << "修改成功！\n\n"
                     << endl;
            }
            else
            {
                cout << "修改失败！\n\n"
                     << endl;
            }
            break;
        }
        case 7:
        {
            cout << "请输入需要修改的位置：" << endl;
            int position;
            cin >> position;
            if (Modify_if_finish(L, position))
            {
                cout << "修改成功！\n\n"
                     << endl;
            }
            else
            {
                cout << "修改失败！\n\n"
                     << endl;
            }
            break;
        }
        case 8:
        {
            cout << "请输入需要删除的位置" << endl;
            int option;
            cin >> option;
            if (Delete_List(L, option))
            {
                cout << "删除成功！\n\n"
                     << endl;
            }
            else
            {
                cout << "删除失败！\n\n"
                     << endl;
            }
            break;
        }
       case 9:
      {
          //查看历史安排日程
          ShowHistory(L);
          break;
      }
        case 10:
        {
            //查看最近日程安排
            ShowNow(L);
            break;
        }
        case 11:
        {
            ShowList(L);
            break;
        }
        case 0:
        {
            cout << "再见！欢迎下次使用！"<< endl;
            exit(1);
        }
        default:
        {
            cout << "您输入的有误，请重新输入！\n\n"
                 << endl;
            break;
        }
        }
    }
    return 0;
}

