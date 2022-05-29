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
