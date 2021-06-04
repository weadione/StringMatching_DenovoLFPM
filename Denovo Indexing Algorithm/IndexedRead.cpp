#include "IndexedRead.h"

IndexedRead::IndexedRead() {
	len = 0;
	rowIndex = 0;
	indexNum = 0;
	isFound = true;
}

IndexedRead::IndexedRead(string value, int rowIndex) {
	indexNum = 0;
	isFound = false;

	this->value = value;
	len = value.size();

	this->rowIndex = rowIndex;
}

IndexedRead::~IndexedRead() {
	colIndex.clear();
}



void IndexedRead::AddIndex(int index, int t) {
	if ( index<t || index>len - 8 - t) {	//suPrefix가 생성불가능한 위치에서 빈도패턴이 발견시 무시
		return;
	}

	colIndex.push_back(index);
	indexNum++;
	isFound = true;
}

void IndexedRead::CalSuPrefix(int t) {
	for (int i = 0; i < colIndex.size(); i++) {
		string tmp = value.substr(colIndex[i] - t, t) + value.substr(colIndex[i] + 8, t);
		suPrefix.push_back(tmp);
	}
}