#pragma once
#include "header.h"

//DenovoLFPM::FindReadIndex()의 과정에서 찾은 ShortRead들을 객체로 저장하기 위해서 만든 클래스
class IndexedRead {
public:
	string value;	//쇼트리드 내용 
	int len;		//쇼트리드 길이
	int rowIndex;	//해당 쇼트리드의 첫 문자의 위치
	vector<int> colIndex;	//해당 쇼트리드에 있는 빈도패턴들의 위치의 집합(한 개의 ShortRead에서 여러 개의 패턴 매칭가능하므로)
	int indexNum;			//colIndex의 개수
	bool isFound;			//빈도패턴이 발견 되었는지 유무(DenovoLFPM::FindReadIndex에서 사용됨)
	vector<string> suPrefix;	/*발견된 빈도패턴의 앞뒤로 t만큼의 접두 접미사 부분을 저장
								만약 AGCTTGCAAA에서 TTGC가 패턴이고 t=3이면
								AGC가 접두부 AAA가 접미부로
								결과적으로 AGCAAA가 저장됨*/

	IndexedRead();		//멤버변수 초기화 생성자로 DenovoLFPM::MergeShortRead()의 과정에서 매칭 성공시 사용
	IndexedRead(string value, int rowIndex);	//멤버변수 초기화 생성자로 DenovoLFPM::FindReadIndex()에서 사용
	~IndexedRead();		//소멸자
	void AddIndex(int index,int t );	//빈도패턴을 찾았을 시 해당 빈도패턴의 인덱스 추가 메서드
	void CalSuPrefix(int t);			//colIndex를 기반으로 suPrefix 생성
};