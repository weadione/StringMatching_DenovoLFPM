#include "DenovoLFPM.h"

DenovoLFPM::DenovoLFPM() {
	Table.InitializeDNA();	//DNA를 새로 생성하는 메서드로 상황에 따라서 주석처리
	Table.FillFrequencyTable();
	Table.SortTable();

	readNum = n;
	shortReadSet = Table.DNA.getShortRead();
	Table.DNA.Clear();	//shortReadSet과 DNA의 멤버변수 ShortRead는 내용이 겹치므로 메모리 효율성를 위해 DNA.Clear()실행
}

void DenovoLFPM::FindReadIndex(string frequencyPattern) {
	indexShortPos.clear();
	deleteShortPos.clear();
	
	istringstream ss(shortReadSet);
	string line, window;
	int rowIndex = 0;
	while (ss >> line) {	//\n을 구분자로 ShortRead를 문장단위로 가져옴
		IndexedRead IndexRead(line, rowIndex);

		for (int colIndex = 0; colIndex < line.size() - 7; colIndex++) {	//가져온 ShortRead 1문장에 대해 frequencyPattern이 있는지 탐색
			window = line.substr(colIndex, 8);
			if (window == frequencyPattern)
				IndexRead.AddIndex(colIndex,t);
		}
	
		if (IndexRead.isFound) {	//패턴이 발견된 경우에만 IndexRead를 목록에 추가함
			IndexRead.CalSuPrefix(t);
			indexShortPos.push_back(IndexRead);
		}

		rowIndex = rowIndex + line.size() + 1;	//ShortRead의 첫 문자 위치 최신화
	}
}

void DenovoLFPM::MergeShortRead() {
	cout << "매칭 알고리즘 시작" << endl;
	int cnt = 0;	//탐색할 빈도수 테이블의 인덱스
	bool isMatch = false;	//매칭이 일어났는지 여부(반복문 탈출에 사용)
	int repeatNum=0;
	int repeatRead = 0;
	while (cnt<65000 && readNum>1){	//빈도수 테이블을 모두 탐색하거나 or 남음 ShortRead의 개수가 1개가 되거나
		if (cnt >= 25000) {	
			if (t > 3) {
				t = 3;
				cnt = 0;
			}
			else
				break;
		}
		if (repeatNum > 5000)	//리드수가 더이상 줄어들지 않은 상태로 5000cnt가 지나면 탈출
			break;
		if (repeatRead == readNum)
			repeatNum++;
		else
			repeatNum = 0;
		repeatRead = readNum;
		//int a = 0;	//디버그용
		//cout << readNum << " "<<cnt<<endl;	//디버그용 주석처리시 속도 상승함

		if (Table.getTableFrequeny()[cnt] <= 1) {	//만약 빈도수 테이블의 결과가 1이면 탈출(ShortRead 탐색결과 1번 나왔다는 의미이므로 더 이상의 탐색은 무의미)
			break;
		}

		FindReadIndex(Table.getTablePattern()[cnt++]);	//cnt번지의 빈도패턴을 가져와서 해당 빈도패턴을 가지는 ShortRead 탐색
		
		if (indexShortPos.size() == 0) {	//디버그용
			//cout << shortreadset;
			continue;
		}
		
		vector<IndexedRead>::iterator iter1 = indexShortPos.begin();
		vector<IndexedRead>::iterator iter2;
		for (int i = 0; i < indexShortPos.size() - 1; i++, iter1++) {	//i,j를 통해 위에서 찾은 모든 ShortRead 비교
			if (isMatch) {	//매칭시 처음부터 다시 탐색을 위한 변수 초기화
				isMatch = false;
				iter1 = indexShortPos.begin();
				//a++;	//디버그용
				//cout << a << endl;
			}
			iter2 = iter1 + 1;
			for (int j = i + 1; j < indexShortPos.size(); j++, iter2++) {
				
				
				for (int num1 = 0; num1 < indexShortPos[i].indexNum; num1++) {	//하나의 ShortRead에서 여러개의 빈도패턴이 발견가능하므로 이것도 모두 비교
					for (int num2 = 0; num2 < indexShortPos[j].indexNum; num2++) {
						if (indexShortPos[i].suPrefix[num1] == indexShortPos[j].suPrefix[num2]) {
							//매칭성공
							isMatch = true;
							IndexedRead NewIndexRead;
							
							//인덱스 앞 부분 합치기 + 앞부분의 기존 빈도패턴 인덱스 이전
							if (indexShortPos[i].colIndex[num1] >= indexShortPos[j].colIndex[num2]) {
								NewIndexRead.value.append(indexShortPos[i].value.substr(0, indexShortPos[i].colIndex[num1]));
								for (int preIndex = 0; preIndex < num1; preIndex++) {
									NewIndexRead.AddIndex(indexShortPos[i].colIndex[preIndex],t);
								}
							}
							else {
								NewIndexRead.value.append(indexShortPos[j].value.substr(0, indexShortPos[j].colIndex[num2]));
								for (int preIndex = 0; preIndex < num2; preIndex++) {
									NewIndexRead.AddIndex(indexShortPos[j].colIndex[preIndex],t);
								}
							}

							//인덱스 뒷부분 합치기 + 뒷부분의 기존 빈도패턴 인덱스 이전
							int preSize = NewIndexRead.value.size() ;
							if (indexShortPos[i].value.substr(indexShortPos[i].colIndex[num1]).size() >= indexShortPos[j].value.substr(indexShortPos[j].colIndex[num2]).size()) {
								NewIndexRead.value.append(indexShortPos[i].value.substr(indexShortPos[i].colIndex[num1]));
								NewIndexRead.len = NewIndexRead.value.size();

								for (int postIndex = num1; postIndex < indexShortPos[i].indexNum; postIndex++) {
									NewIndexRead.AddIndex(indexShortPos[i].colIndex[postIndex]+preSize- indexShortPos[i].colIndex[num1],t);
								}
								
							}
							else {
								NewIndexRead.value.append(indexShortPos[j].value.substr(indexShortPos[j].colIndex[num2]));
								NewIndexRead.len = NewIndexRead.value.size();

								for (int postIndex = num2; postIndex < indexShortPos[j].indexNum; postIndex++) {
									NewIndexRead.AddIndex(indexShortPos[j].colIndex[postIndex] + preSize - indexShortPos[j].colIndex[num2],t);
								}
							}
							deleteShortPos.push_back(indexShortPos[j]);	//매칭성공했으므로 중복 매칭 방지를 위해 사용된 ShortRead를 삭제 리스트에 삽입
							deleteShortPos.push_back(indexShortPos[i]);

							indexShortPos.erase(iter2);	//기존 목록에서 삭제(뒤에서부터)
							indexShortPos.erase(iter1);

							NewIndexRead.CalSuPrefix(t);	//새로운 suPrefix 계산
							NewIndexRead.rowIndex = shortReadSet.size();

							shortReadSet.append(NewIndexRead.value );	//매칭되어 새롭게 생성된 NewShortRead 내용을 삽입
							shortReadSet.append("\n");
							indexShortPos.push_back(NewIndexRead);



							readNum--;	//ShortRead 개수 한개 줄임
							iter1 = indexShortPos.begin();	//새로운 ShortRead가 들어왔으므로 처음부터 다시 매칭
							i = -1;	//i++을 고려한 초기화
						}
						if (isMatch)
							break;
					}
					if (isMatch)
						break;
				}
				if (isMatch)
					break;
			}
		}

		IndexedRead InfValue("a", INT_MAX);		//deleteShortPos의 정렬 과정중 오류 방지를 위한 inf값 삽입
		deleteShortPos.push_back(InfValue);

		SortDeletePos(0, deleteShortPos.size() - 1);	/*가장 뒤에 위치하는 ShortRead부터 삭제해야 오류가 안나므로 
														각 ShortRead의 시작 인덱스 값(rowIndex)를 기준으로 오름차순 정렬*/

		for (int i = deleteShortPos.size()-2; i >= 0 ; i--)
			shortReadSet.erase(deleteShortPos[i].rowIndex, deleteShortPos[i].len + 1);	//매칭이 완료된 ShortRead들 뒤에서부터 삭제
	}

}


int DenovoLFPM::QuickPartition(int left, int right) {
	int pivot, intValue;
	IndexedRead ReadValue;

	pivot = left;
	intValue = deleteShortPos[pivot].rowIndex;
	ReadValue = deleteShortPos[pivot];

	do {
		do {
			left++;
		} while (deleteShortPos[left].rowIndex < intValue);

		do {
			right--;
		} while (deleteShortPos[right].rowIndex > intValue);

		if (left < right) {
			IndexedRead tmpRead = deleteShortPos[left];
			deleteShortPos[left] = deleteShortPos[right];
			deleteShortPos[right] = tmpRead;
		}
		else
			break;

	} while (true);

	deleteShortPos[pivot] = deleteShortPos[right];
	deleteShortPos[right] = ReadValue;

	return right;
}

void DenovoLFPM::SortDeletePos(int left, int right) {
	int pivot;
	if (left < right) {
		pivot = QuickPartition(left, right + 1);
		SortDeletePos(left, pivot - 1);
		SortDeletePos(pivot + 1, right);
	}
}

void DenovoLFPM::print() {
	ofstream fout("Result.txt");
	if (!fout) {
		cout << "Result.txt 쓰기 실패" << endl;
		exit(1);
	}

	fout << shortReadSet;

	fout.close();
}


void DenovoLFPM::GetAccuracy() {
	string myDNA = Table.DNA.getMyDNA();
	istringstream ss(shortReadSet);

	string line, window;
	int rowIndex = 0;
	int num = 0;
	int maxMatch = 0;
	cout << "<매칭 결과>" << endl << readNum << "개의 문자열로 매칭됨" << endl;
	while (ss >> line) {	//\n을 구분자로 ShortRead를 문장단위로 가져옴
		num++;
		maxMatch = 0;
		for (int i = 0; i < M - line.size() + 1; i++) {
			int match = 0;
			for (int j=0; j < line.size(); j++) {
				if (myDNA[i+j] == line[j])
					match++;
			}
			if (maxMatch < match)
				maxMatch = match;

		}
		cout << num << "번: " << ((double)maxMatch / (double)M) * 100 << "%" << endl;
	}
}

int main() {
	clock_t start, finish;
	double duration;

	start = clock();
	DenovoLFPM test;
	test.MergeShortRead();
	finish = clock();

	test.print();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << duration << "초 소요" << endl;
	test.GetAccuracy();
}