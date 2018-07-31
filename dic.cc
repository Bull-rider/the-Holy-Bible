 ///:
 /// @file    dic.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-30 18:03:11
 ///
 
#include <string.h>
#include<time.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
struct Recad
{
	string word;
	int freq;
	bool operator<(const Recad &rhs) const
	{
		return freq>rhs.freq;
	}
};
class Dictionary
{

	public:
		Dictionary()
		{
			_dict.reserve(15000);
		}
		void read(const string &filename);
		void store(const string &filename);
	private:
		string dictionaryword(string &word);//read()函数调用
		void statistic(const string &word);//store()函数调用
	private:
		vector<Recad> _dict;
};
//读取单词时/单词处理函数
string Dictionary::dictionaryword(string &word)
{
	int idx;
	for(size_t idx=0;idx!=word.size();++idx)
	{
		//是数字直接返回空字符串
		if(isdigit(word[idx]))
		{
			return string();
		}
		//大写变 小写
		else if(isupper(word[idx]))
		{
			word[idx]=tolower(word[idx]);
		}
	}
	return word;
}
//存放单词时需要调用的函数
void Dictionary::statistic(const string &word)
{
	//遍历类中对象，如果单词存在就把相应的对象的freq加1
	size_t idx;
	for(idx=0;idx!=_dict.size();++idx)
	{
		if(_dict[idx].word==word)
		{
			_dict[idx].freq++;
			break;
		}
	}
	//如果不在类中就把单词添加到类中
	if(idx==_dict.size())
	{
		Recad recad;
		recad.word=word;
		recad.freq=1;
		_dict.push_back(recad);
	}
}
void Dictionary::read(const string &filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout<<"error ifs:"<<endl;
	}
	string line;
	while(getline(ifs,line))//每次读取一行
	{
		istringstream iss(line);
		string reword;
		while(iss>>reword)//从字符串流中每次读取一个单词，并对单词做处理
		{
			string word=dictionaryword(reword);
			statistic(word);
		}
	}
	std::sort(_dict.begin(),_dict.end());
}
void Dictionary::store(const string &filename)
{
	ofstream ofs(filename);
	if(!ofs)
	{
		cout<<"error ofs:"<<endl;
	}
	for(auto &recad:_dict)
	{
		ofs<<recad.word<<"\t"<<recad.freq<<"\n";
	}
}
int main()
{
	time_t start,end;
	Dictionary dic;
	//dic.read("The_Holy_Bible.txt");
	start=time(NULL);
	dic.read("file.txt");
	dic.store("New.txt");
	end=time(NULL);
	cout<<"用时:"<<end-start<<"s"<<endl;
	return 0;
}
