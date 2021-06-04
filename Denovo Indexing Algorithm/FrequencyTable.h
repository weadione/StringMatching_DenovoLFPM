#pragma once
#include "header.h"
#include "GenerateDNA.h"

class FrequencyTable {
private:

	string* tablePattern;	//4^8개의 길이 8짜리 가능한 모든 AGCT의 배열 (이하 빈도패턴)
	int* tableFrequency;	//위 AGCT배열의 원소가 shortRead에서 등장하는 빈도수
	
	int QuickPartition(int left, int right);	//퀵소트 파티션 메서드(내림차순)

public:
	GenerateDNA DNA;	//dna 객체(DNA, ShortRead 정보 가짐)

	FrequencyTable();		
	void InitializeDNA();			//새로운 DNA와 shortRead 생성
	void FillFrequencyTable();		//shortRead 빈도수 측정
	void SortTable(int left=0, int right = pow(4, 8) - 1);	//퀵소트를 사용해 테이블을 내림차순으로 정렬하는 메서드
	void printTable();				//디버그용 테이블 출력 메서드
	int* getTableFrequeny();		//tableFrequency를 반환하는 메서드
	string* getTablePattern();		//tablePattern을 반환하는 메서드
};