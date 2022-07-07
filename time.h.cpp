#include<iostream>
#include<time.h>
using namespace std;
/*
struct tm
{
	int tm_sec;   // seconds after the minute - [0, 60] including leap second
	int tm_min;   // minutes after the hour - [0, 59]
	int tm_hour;  // hours since midnight - [0, 23]
	int tm_mday;  // day of the month - [1, 31]
	int tm_mon;   // months since January - [0, 11]
	int tm_year;  // years since 1900
	int tm_wday;  // days since Sunday - [0, 6]
	int tm_yday;  // days since January 1 - [0, 365]
	int tm_isdst; // daylight savings time flag
};
*/
int main() {
	//time()及ctime()函数应用
	time_t* current_time = new time_t;
	time(current_time);
	*current_time = time(nullptr);//time()函数的两种使用方式
	cout << "从1970年1月1日(UTC)至今的秒数为:" << *current_time << "s" << endl;
	char arr[26];//26为表示时间的最小字符串长度
	ctime_s(arr, 26, current_time);//将time_t中的时间转化为字符串(经过时区转换)
	cout << "当前北京时间为:" << arr;

	//gmtime()及localtime()函数应用
	tm* current_date = new tm;
	tm* current_date_beijing = new tm;
	gmtime_s(current_date, current_time);//将time_t表示的时间转换为tm表示的时间
	localtime_s(current_date_beijing, current_time);//将time_t表示的时间转换为的tm表示的时间(经过时区转换)
	
	//asctime()函数应用
	asctime_s(arr, current_date);//将tm结构中的时间转化为字符串
	cout << "当前UTC时间为: " << arr;
	asctime_s(arr, current_date_beijing);
	cout << "当前北京时间为:" << arr;

	//mktime()函数应用
	*current_time = mktime(current_date);//将tm表示的时间转换为time_t表示的时间
	ctime_s(arr, 26, current_time);//将time_t中的时间转化为字符串(经过时区转换)
	cout << "当前UTC时间为: " << arr;

	//clock()函数应用
	clock_t	start = clock();//记录循环初始时处理器时间
	for (int i = 0; i < 1000000; i++) {
		arr[0]++;
	}
	clock_t end = clock();//记录循环结束时处理器时间
	double second = double(end - start) / CLOCKS_PER_SEC;//将处理器时间转化为秒
	cout << "\n运行该循环耗时:" << second << "s" << endl;
	cin.get();
}
