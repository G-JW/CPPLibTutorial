#include <iostream>
#include <fstream>
#include <direct.h>
#include <io.h>
using namespace std;
/*
ios::in         打开文件用于读取数据。如果文件不存在，则打开出错。
ios::out        打开文件用于写入数据。如果文件不存在，则新建该文件；如果文件原来就存在，则打开时清除原来的内容。
ios::app        打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件。
ios::ate        打开一个已有的文件，并将文件读指针指向文件末尾。如果文件不存在，则打开出错。
ios::trunc      打开文件时会清空内部存储的所有数据，单独使用时与 ios::out 相同。
ios::binary     以二进制方式打开文件。若不指定此模式，则以文本模式打开。
ios::nocreate   不建立文件，所以文件不存在时打开失败。
ios::noreplace  不覆盖文件，所以打开文件时如果文件存在失败。
*/
string getPath(string, string);//由路径和文件名得到文件路径
int createFolder(string);//创建文件夹
int deleteFolder(string);//删除文件夹
void createFile(string);//新建文件或清空文件内容
void deleteFile(string);//删除文件
void searchFile(string);//判断文件是否存在

int main()
{
    fstream iof;
    ofstream outf;
    ifstream inf;
    string foldername("testfolder");
    string filename("test.txt");
    string filepath = getPath(foldername, filename);

    //判断文件夹或文件是否存在
    if (_access(foldername.c_str(), 0) == 0)
        cout << "存在" << endl;
    else if (_access(foldername.c_str(), 0) == -1)
        cout << "不存在" << endl;

    //文件夹和文件的创建与删除
    createFolder(foldername);
    searchFile(filepath);
    createFile(filepath);
    deleteFile(filepath);
    deleteFolder(foldername);

    //文件流指针的使用
    outf.open(filename, ios::out);
    inf.open(filename, ios::in);
    outf.tellp();//获取输出流指针的位置
    inf.tellg();//获取输入流指针的位置
    outf << "abcdef";
    outf.seekp(0);//设置输出流指针到指定位置
    outf << "12";
    outf.close();
    inf.seekg(0);//设置输出流指针到指定位置
    cout << char(inf.get()) << endl;
    inf.close();

    //文件的中文写入与读入
    string buffer;
    outf.open(filename, ios::out);
    outf << "中文测试" << endl;
    cout << "请输入字符串：";
    cin >> buffer;
    outf << buffer << endl;
    outf.close();
    inf.open(filename, ios::in);
    inf >> buffer;
    cout << buffer;
    inf >> buffer;
    cout << buffer << endl;
    inf.close();
    deleteFile(filename);
}

string getPath(string foldername, string filename)
{
    return string(foldername + "\\" + filename);
}

int createFolder(string foldername)
{
    int temp;
    temp = _mkdir(foldername.c_str());
    if (temp == 0)
        cout << "成功创建文件夹" << foldername << endl;
    else if(temp == -1)
        cout << "文件夹" << foldername << "已存在" << endl;
    return temp;
}

int deleteFolder(string foldername)
{
     int temp;
     temp = _rmdir(foldername.c_str());
     if (temp == 0)
         cout << "成功删除文件夹" << foldername << endl;
     else if (temp == -1)
         cout << "文件夹" << foldername << "不存在" << endl;
     return temp;
}

void createFile(string filename)
{
    ofstream temp;
    temp.open(filename, ios::out);
    temp.close();
}

void deleteFile(string filename)
{
    int temp;
    temp = remove(filename.c_str());
    if (temp == 0)
        cout << "成功删除" << filename << endl;
    else
        cout << filename << "删除失败" << endl;
}

void searchFile(string filename)
{
    ifstream temp;
    temp.open(filename, ios::in);
    if (temp.is_open())
        cout << "文件" << filename << "已存在" << endl;
    else
        cout << "文件" << filename << "不存在" << endl;
    temp.close();
}