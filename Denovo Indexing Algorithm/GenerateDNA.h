#pragma once
#include "header.h"


class GenerateDNA {
private:
	string myDNA, shortRead;	//DNA, ShortRead 저장

	void SaveDNA(string randomDNA, string fileName);	//fileName.txt에 해당 randomDNA 저장 메서드
	string LoadDNA(string fileName);					//fileName.txt의 내용 반환 메서드
public:
	GenerateDNA();		//기존에 저장된 DNA, ShortRead 읽어서 저장 생성자
	void MkDNA();		//기존 저장된 DNA위에 새로운 DNA 덮어쓰기 메서드
	void MkShortRead();	//기존 저장된 ShortRead위에 새로운 ShortRead 덮어쓰기 메서드
	string getMyDNA();	//myDNA반환 메서드
	string getShortRead();	//ShortRead 반환 메서드
	void Clear();		//메모리 공간을 아끼기위한  myDNA, shortRead 삭제 메서드
};
