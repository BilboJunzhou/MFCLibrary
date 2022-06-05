
文章示例程序下载地址：
[https://download.csdn.net/download/weixin_51717597/85422178](https://download.csdn.net/download/weixin_51717597/85422178)
github完整项目源码
[https://github.com/BilboJunzhou/MFCLibrary](https://github.com/BilboJunzhou/MFCLibrary)

# 图书馆管理系统需求
1、图书管理基本业务模拟  
1) 书的登记内容包括书号、书名、著作者、现存量和库存量；
2) 建立索引表（线性表）以提高查找效率；
a)采编入库：新购一种书，确定书号后，登记到图书帐目表中，如果表中已有，则只将库存量增加；
b)借阅：如果一种书的现存量大于0，则借出一本，登记借阅者的书证号和归还期限，改变现存量；
c)归还：注销对借阅者的登记，改变该书的现存量。
3) 主要功能如下：
输出形式：能按书号、书名、著作者查找库存的书籍信息
          能按学生的借书证号显示学生信息和借阅信息
          书籍入库
          借书功能实现
          还书功能实现
        
# 设计思想
## 后端数据处理
利用面向对象思想，实例对象书和学生，对两者附加相关方法和属性，同时使用XML对文件信息进行存储，方法为调用tinystr.h的一个xml读写库。之后将其封装为静态lib库进行接口调用
## 可视化实现
使用MFC进行窗口编写，实现图书馆可视化。
# 效果展示

[video(video-ugdIu0Xx-1653024401151)(type-bilibili)(url-https://player.bilibili.com/player.html?aid=256730209)(image-https://img-blog.csdnimg.cn/img_convert/4d0fbf713f44c68e26081d7f078489db.png)(title-)]
# 后端代码
注：首先在官网下载xml文件包，链接：[https://sourceforge.net/projects/tinyxml/](https://sourceforge.net/projects/tinyxml/)
引入自己的库，然后开始实现接口，写好后端接口封装为lib静态库，根据接口撰写前端可视化就好啦。
## LibraryMes.h
```c
#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#define FENGZHUANGCPP_API __declspec(dllexport)

class FENGZHUANGCPP_API Library
{
public:
	class StudentS {
	public:
		// 变量
		struct StudentMes
		{
			int stu_num = 0;								// 学生借阅号
			std::string stu_name = 0;						// 学生姓名
			std::pair<int, string> stu_borrow1 = { 0,"" };	// 借阅书籍信息1（书号，时间）
			std::pair<int, string> stu_borrow2 = { 0,"" };;	// 借阅书籍信息2（书号，时间）
			StudentMes() :stu_num(0), stu_name(""), stu_borrow1({ 0,"" }), stu_borrow2({ 0,"" }) {}
			StudentMes(std::string name, int num) :stu_name(name), stu_num(num), stu_borrow1({ 0, "" }), stu_borrow2({ 0, "" }) {}
		};
		std::unordered_map<int, StudentMes*> stu_hash_save;		// 通过字典存储学生学号和信息，key为学生学号，val为学生信息
		std::vector<StudentMes*> stu_mes_save;					// 将所有学生信息存储到容器中
		// 方法
		void writeStuXml();																// 将学生信息写入xml文件
		void getStuMes(string name, int num);											// 键盘读取学生信息
		bool saveStuMes();																// 从student.xml文件中读取学生信息，存储到哈希表和容器，同时也是初始化函数
		StudentMes* searchStuMes(int stu_number);											// 输入学号，返回学生对应信息的指针
		StudentMes* searchStuName(string name);											// 输入姓名，返回学生对应信息的指针
		//void showStuMes(int stu_num_search);						// 输入学号，输出该学生所有信息
		//void showStuMes();											// 输出所有学生所有信息
	};

	class BookS {
	public:
		// 变量
		struct Book
		{
			int book_num = 0;						// 书籍号
			std::string book_name = "";				// 书名
			std::string writer = "";				// 作者
			int now_save = 0;						// 现存量
			int all_save = 0;						// 库存量
			std::vector<int> book_borrow;			// 书籍借阅信息

			Book() :book_num(0), book_name(""), writer(""), now_save(0), all_save(0), book_borrow(NULL) {}
			Book(int book_num, std::string s1, std::string s2) :book_num(book_num), book_name(s1), writer(s2), now_save(1), all_save(1), book_borrow(NULL) {}
		};
		vector<Book*> book_save;
		unordered_map<int, Book*> book_num_hash;
		unordered_map<string, Book*> book_name_hash;
		// 方法
		void writeBookMes(string name,int num,string wirter);	// 建立图书信息
		void writeStuXml();												// 将图书信息写入xml文件 
		Book* searchBookName(string name_of_book);		// 通过书名查找
		vector<Book*> searchBookWriter(string writer_book);				// 通过作者查找
		Book* searchBookNum(int num_of_book);			// 通过书籍号查找
		bool saveBookMes();	// 变量初始化函数/将xml文件数据读取至代码
	};
	bool borrowBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run);			// 借书
	bool returnBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run);			// 还书	
};

#endif // !LIBRARY_H
```
## LibraryMes.cpp
```c
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <time.h>
#pragma warning( disable : 4996 )
#include "tinyxml.h"
#define STUDENT_FILE "student"
#define BOOKS_FILE   "book"
using namespace std;
#include "LibraryMes.h"

//struct StudentMes
//{
//	int stu_num;						// 学生借阅号
//	std::string stu_name;				// 学生姓名
//	std::pair<int, string> stu_borrow1;	// 借阅书籍信息1（书号，时间）
//	std::pair<int, string> stu_borrow2;	// 借阅书籍信息2（书号，时间）
//	StudentMes() :stu_num(0), stu_name(""), stu_borrow1({ 0,"" }), stu_borrow2({ 0,"" }) {}
//	StudentMes(std::string name, int num) :stu_name(name), stu_num(num), stu_borrow1({ 0, "" }), stu_borrow2({ 0, "" }) {}
//};
void addChile(TiXmlElement* parent, const char* node, int value)
{
	//创建节点

	TiXmlElement* xml_node = new TiXmlElement(node);
	//将int转为char
	//char buf[32];
	string data = to_string(value);
	char* buff = (char*)data.data();
	xml_node->LinkEndChild(new TiXmlText(buff));
	parent->LinkEndChild(xml_node);

}
void addChile(TiXmlElement* parent, const char* node, const char* value)
{
	//创建节点
	TiXmlElement* xml_node = new TiXmlElement(node);
	//将int转为char
	xml_node->LinkEndChild(new TiXmlText(value));
	parent->LinkEndChild(xml_node);
}
void Library::StudentS::writeStuXml()
{
	TiXmlDocument xml;
	xml.LinkEndChild(new TiXmlDeclaration("1.0", "GBK", ""));
	TiXmlElement* xml_root = new TiXmlElement("root");
	xml.LinkEndChild(xml_root);
	for (int i = 0; i < stu_mes_save.size(); i++)
	{
		StudentMes* node = stu_mes_save[i];
		//创建一个节点
		string node_name = "student";
		TiXmlElement* xml_node = new TiXmlElement((char*)node_name.data());
		xml_root->LinkEndChild(xml_node);
		//创建第一个子节点
		if (true)
		{
			addChile(xml_node, "id", node->stu_num);
			addChile(xml_node, "name", (char*)node->stu_name.data());
			addChile(xml_node, "borrowBook1", node->stu_borrow1.first);
			addChile(xml_node, "borrowTime1", (char*)node->stu_borrow1.second.data());
			addChile(xml_node, "borrowBook2", node->stu_borrow2.first);
			addChile(xml_node, "borrowTime2", (char*)node->stu_borrow2.second.data());

		}
	}
	xml.SaveFile(STUDENT_FILE".xml");
}

void Library::StudentS::getStuMes(string name,int num)
{

	StudentMes* node = new StudentMes(name, num);
	stu_mes_save.push_back(node);
	writeStuXml();
}

bool Library::StudentS::saveStuMes()
{
	//开始解析
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(STUDENT_FILE".xml"))return -1;
	//获取根元素
	TiXmlElement* xml_root = xml_doc.RootElement();
	if (xml_root == NULL)return false;
	TiXmlElement* xml_note = xml_root->FirstChildElement("student");
	stu_hash_save.clear();
	stu_mes_save.clear();
	while (xml_note)
	{
		StudentMes* stusave = new StudentMes();
		TiXmlElement* xml_id = xml_note->FirstChildElement("id");
		auto aid = xml_id->GetText();
		stusave->stu_num = atoi(aid);
		TiXmlElement* xml_name = xml_note->FirstChildElement("name");
		auto aname = xml_name->GetText();
		stusave->stu_name = string(aname);
		TiXmlElement* xml_num1 = xml_note->FirstChildElement("borrowBook1");
		auto anum1 = xml_num1->GetText();
		stusave->stu_borrow1.first = atoi(anum1);
		TiXmlElement* xml_str1 = xml_note->FirstChildElement("borrowTime1");
		auto atime1 = xml_str1->GetText();
		if (atime1)
			stusave->stu_borrow1.second = string(atime1);
		TiXmlElement* xml_num2 = xml_note->FirstChildElement("borrowBook2");
		auto anum2 = xml_num2->GetText();
		stusave->stu_borrow2.first = atoi(anum2);
		TiXmlElement* xml_str2 = xml_note->FirstChildElement("borrowTime2");
		auto atime2 = xml_str2->GetText();
		if (atime2)
			stusave->stu_borrow1.second = string(atime2);
		stu_hash_save.insert(pair<int, StudentMes*>(stusave->stu_num, stusave));	//  存储哈希指
		stu_mes_save.push_back(stusave);											//  容器存储学生编号
		//指向下一个兄弟节点
		xml_note = xml_note->NextSiblingElement();
	}
	return true;
}

Library::StudentS::StudentMes* Library::StudentS::searchStuMes(int stu_number)
{
	StudentMes* result;
	if (stu_hash_save.find(stu_number) != stu_hash_save.end())
	{
		result = stu_hash_save.at(stu_number);
		return result;
	}
	return NULL;
}

Library::StudentS::StudentMes* Library::StudentS::searchStuName(string name)
{
	for (auto a : stu_mes_save) {
		if (name == a->stu_name)
		{
			return a;
		}
	}
	return NULL;
}


void Library::BookS::writeBookMes(string name, int num, string wirter)
{
	if (book_num_hash.find(num) != book_num_hash.end()) {
		book_num_hash.at(num)->all_save++;
		book_num_hash.at(num)->now_save++;
	}
	else
	{
		Book* node = new Book(num, name, wirter);
		book_save.push_back(node);
		book_name_hash.insert(pair<string, Book*>(name, node));
		book_num_hash.insert(pair<int, Book*>(num, node));
	}
	writeStuXml();
}

void Library::BookS::writeStuXml()
{
	TiXmlDocument xml;
	xml.LinkEndChild(new TiXmlDeclaration("1.0", "GBK", ""));
	TiXmlElement* xml_root = new TiXmlElement("root");
	xml.LinkEndChild(xml_root);
	for (int i = 0; i < book_save.size(); i++)
	{
		Book* node = book_save[i];
		//创建一个节点
		string node_name = "book";
		TiXmlElement* xml_node = new TiXmlElement((char*)node_name.data());
		xml_root->LinkEndChild(xml_node);
		if (true)
		{
			addChile(xml_node, "id", node->book_num);
			addChile(xml_node, "name", (char*)node->book_name.data());
			addChile(xml_node, "writer", (char*)node->writer.data());
			addChile(xml_node, "allSave", node->all_save);
			addChile(xml_node, "nowSave", node->now_save);
			string BorrowNum = "BorrowNum";
			TiXmlElement* xml_node_sert = new TiXmlElement((char*)BorrowNum.data());
			xml_node->LinkEndChild(xml_node_sert);
			if (!node->book_borrow.empty()) {
				for (int j : node->book_borrow) {
					addChile(xml_node_sert, "borrowID", j);
				}
			}
		}
	}
	xml.SaveFile(BOOKS_FILE".xml");
}

Library::BookS::Book* Library::BookS::searchBookName(string name_of_book)
{
	Book* result = NULL;
	if (book_name_hash.find(name_of_book) != book_name_hash.end())
	{
		result = book_name_hash.at(name_of_book);
	}
	return result;
}

vector<Library::BookS::Book*> Library::BookS::searchBookWriter(string writer_book)
{
	vector<Book*>result;
	for (Book* a : book_save) {
		if (a->writer == writer_book)
		{
			result.push_back(a);
		}
	}
	return result;
}

Library::BookS::Book* Library::BookS::searchBookNum(int num_of_book)
{
	Book* result = NULL;
	if (book_num_hash.find(num_of_book) != book_num_hash.end())
	{
		result = book_num_hash.at(num_of_book);
	}
	return result;
}

bool Library::BookS::saveBookMes()
{
	//开始解析
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(BOOKS_FILE".xml"))return -1;
	//获取根元素
	TiXmlElement* xml_root = xml_doc.RootElement();
	if (xml_root == NULL)return false;
	TiXmlElement* xml_note = xml_root->FirstChildElement("book");
	book_num_hash.clear();
	book_name_hash.clear();
	book_save.clear();
	while (xml_note)
	{
		Book* stusave = new Book();
		TiXmlElement* xml_id = xml_note->FirstChildElement("id");
		auto aid = xml_id->GetText();
		stusave->book_num = atoi(aid);
		TiXmlElement* xml_name = xml_note->FirstChildElement("name");
		auto aname = xml_name->GetText();
		stusave->book_name = string(aname);
		xml_name = xml_note->FirstChildElement("writer");
		auto anWame = xml_name->GetText();
		stusave->writer = string(anWame);
		TiXmlElement* xml_num1 = xml_note->FirstChildElement("allSave");
		aid = xml_num1->GetText();
		stusave->all_save = atoi(aid);
		TiXmlElement* xml_str1 = xml_note->FirstChildElement("nowSave");
		aid = xml_str1->GetText();
		stusave->now_save = atoi(aid);
		TiXmlElement* xml_boor = xml_note->FirstChildElement("BorrowNum")->FirstChildElement("BorrowID");
		while (xml_boor) {
			auto c = xml_boor->GetText();
			stusave->book_borrow.push_back(atoi(c));
			xml_boor = xml_boor->NextSiblingElement();
		}
		book_num_hash.insert(pair<int, Book*>(stusave->book_num, stusave));	//  存储哈希指
		book_name_hash.insert(pair<string, Book*>(stusave->book_name, stusave));
		book_save.push_back(stusave);
		//指向下一个兄弟节点
		xml_note = xml_note->NextSiblingElement();
	}
	return true;
}

bool Library::borrowBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run)
{
	BookS::Book* book_mes = Book_run.searchBookNum(book_num);
	StudentS::StudentMes* stu_mes = stu_run.searchStuMes(stu_num);
	if (book_mes->book_num && stu_mes->stu_num && book_mes->now_save)
	{
		
		if (!stu_mes->stu_borrow1.first || !stu_mes->stu_borrow2.first)
		{
			book_mes->now_save--;
			book_mes->book_borrow.push_back(stu_mes->stu_num);
			time_t t = time(0);
			char tmp[32] = { NULL };
			strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
			if (!stu_mes->stu_borrow1.first) {
				stu_mes->stu_borrow1.first = book_mes->book_num;
				stu_mes->stu_borrow1.second = string(tmp);
			}
			else {
				stu_mes->stu_borrow2.first = book_mes->book_num;
				stu_mes->stu_borrow2.second = string(tmp);
			}
			
			stu_run.writeStuXml();
			Book_run.writeStuXml();
			return true;
		}
	}
	return false;
}

bool Library::returnBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run)
{
	BookS::Book* book_mes = Book_run.searchBookNum(book_num);
	StudentS::StudentMes* stu_mes = stu_run.searchStuMes(stu_num);
	if (book_mes->book_num && stu_mes->stu_num)
	{
		if (stu_mes->stu_borrow1.first == book_num || stu_mes->stu_borrow2.first == book_num) {
			book_mes->now_save++;
			if (stu_mes->stu_borrow2.first == book_num) {
				stu_mes->stu_borrow2.first = 0;
				stu_mes->stu_borrow2.second = "";
			}
			else {
				stu_mes->stu_borrow1.first = 0;
				stu_mes->stu_borrow1.second = "";
			}
			
			for (int i = 0; i < book_mes->book_borrow.size(); i++)if (book_mes->book_borrow[i] == stu_mes->stu_num){
				book_mes->book_borrow.erase(book_mes->book_borrow.begin() + i);
				break;
			}
			stu_run.writeStuXml();
			Book_run.writeStuXml();
			return true;
		}
	}
	return false;
}
```
