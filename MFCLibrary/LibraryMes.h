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
		// ����
		struct StudentMes
		{
			int stu_num = 0;								// ѧ�����ĺ�
			std::string stu_name = 0;						// ѧ������
			std::pair<int, string> stu_borrow1 = { 0,"" };	// �����鼮��Ϣ1����ţ�ʱ�䣩
			std::pair<int, string> stu_borrow2 = { 0,"" };;	// �����鼮��Ϣ2����ţ�ʱ�䣩
			StudentMes() :stu_num(0), stu_name(""), stu_borrow1({ 0,"" }), stu_borrow2({ 0,"" }) {}
			StudentMes(std::string name, int num) :stu_name(name), stu_num(num), stu_borrow1({ 0, "" }), stu_borrow2({ 0, "" }) {}
		};
		std::unordered_map<int, StudentMes*> stu_hash_save;		// ͨ���ֵ�洢ѧ��ѧ�ź���Ϣ��keyΪѧ��ѧ�ţ�valΪѧ����Ϣ
		std::vector<StudentMes*> stu_mes_save;					// ������ѧ����Ϣ�洢��������
		// ����
		void writeStuXml();																// ��ѧ����Ϣд��xml�ļ�
		void getStuMes(string name, int num);											// ���̶�ȡѧ����Ϣ
		bool saveStuMes();																// ��student.xml�ļ��ж�ȡѧ����Ϣ���洢����ϣ���������ͬʱҲ�ǳ�ʼ������
		StudentMes* searchStuMes(int stu_number);											// ����ѧ�ţ�����ѧ����Ӧ��Ϣ��ָ��
		StudentMes* searchStuName(string name);											// ��������������ѧ����Ӧ��Ϣ��ָ��
		//void showStuMes(int stu_num_search);						// ����ѧ�ţ������ѧ��������Ϣ
		//void showStuMes();											// �������ѧ��������Ϣ
	};

	class BookS {
	public:
		// ����
		struct Book
		{
			int book_num = 0;						// �鼮��
			std::string book_name = "";				// ����
			std::string writer = "";				// ����
			int now_save = 0;						// �ִ���
			int all_save = 0;						// �����
			std::vector<int> book_borrow;			// �鼮������Ϣ

			Book() :book_num(0), book_name(""), writer(""), now_save(0), all_save(0), book_borrow(NULL) {}
			Book(int book_num, std::string s1, std::string s2) :book_num(book_num), book_name(s1), writer(s2), now_save(1), all_save(1), book_borrow(NULL) {}
		};
		vector<Book*> book_save;
		unordered_map<int, Book*> book_num_hash;
		unordered_map<string, Book*> book_name_hash;
		// ����
		void writeBookMes(string name,int num,string wirter);	// ����ͼ����Ϣ
		void writeStuXml();												// ��ͼ����Ϣд��xml�ļ� 
		Book* searchBookName(string name_of_book);		// ͨ����������
		vector<Book*> searchBookWriter(string writer_book);				// ͨ�����߲���
		Book* searchBookNum(int num_of_book);			// ͨ���鼮�Ų���
		bool saveBookMes();	// ������ʼ������/��xml�ļ����ݶ�ȡ������
	};
	bool borrowBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run);			// ����
	bool returnBook(int book_num, int stu_num, StudentS stu_run, BookS Book_run);			// ����	
};

#endif // !LIBRARY_H
