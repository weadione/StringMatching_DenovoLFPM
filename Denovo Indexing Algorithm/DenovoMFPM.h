#pragma once
#include "header.h"
#include"FrequencyTable.h"
#include "IndexedRead.h"

class DenovoMFPM {
private:
	FrequencyTable Table;	//빈도수 테이블 객체
	vector<IndexedRead> indexShortPos;	//같은 빈도패턴을 가지는 ShortRead들의 목록
	vector<IndexedRead> deleteShortPos;	//매칭이 되어서 삭제해야할 ShortRead들의 목록
	mutex m;

	string shortReadSet;		//ShortRead의 전체 문자열
	int readNum;			//남아있는 ShortReadd의 개수
	int t = 5;	/*찾은 인덱스 앞뒤로 탐색할 길이
				(ex. 만약 t가 4이면 8개의 매칭된 패턴 앞뒤로 각각 4개씩 더 비교해
				총 16개가 같아야 이어진 read라고 판별)*/

	int QuickPartition(int left, int right);	//퀵소트 파티션 메서드(오름차순)
	void SortDeletePos(int left, int right);	//퀵소트를 사용해 deleteShortPos을 오름차순으로 정렬하는 메서드

public:
	DenovoMFPM();	//Table객체의 메서드 실행 및 멤버변수 초기화 생성자
	void FindReadIndex(string frequencyPattern);	//frequencyPattern을 가지고 있는 ShortRead들을 탐색해서 indexShortPos에 추가
	void ThreadFindReadIndex(string frequencyPattern, string shortRead, int rowIndex, mutex& m);	//멀티스레딩을 위한 함수
	void MergeShortRead();	//매칭 알고리즘(핵심알고리즘)
	void print();	//Result.txt파일에 실행결과로 나온 DNA 저장
	void GetAccuracy();		//정확도 계산 및 출력
};