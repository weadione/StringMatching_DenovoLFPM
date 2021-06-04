#include "FrequencyTable.h"

FrequencyTable::FrequencyTable() {
	ifstream fin;
	fin.open("frequencyString.txt");	//미리 4^8개의 패턴을 저장해둔 파일

	int rowLen = pow(4, 8) + 1;		//퀵소트 오류방지를 위해 1추가

	tablePattern = new string[rowLen];	//멤버변수 초기화
	tableFrequency = new int[rowLen];
	for (int i = 0; i < rowLen; i++) {
		tableFrequency[i] = 0;
		getline(fin, tablePattern[i]);
	}

	tableFrequency[rowLen] = INT_MIN;	//퀵소트 오류 방지용 -inf값 
}

void FrequencyTable::InitializeDNA() {
	DNA.MkDNA();
	DNA.MkShortRead();
}

void FrequencyTable::FillFrequencyTable() {
	string shortReads = DNA.getShortRead();
	istringstream ss(shortReads);

	string line, window;
	while (ss>>line){	//\n을 구분자로 ShortRead를 문장단위로 가져옴
		for (int i = 0; i < k - 7; i++) {
			int frequencyIndex = 0;
			window = line.substr(i, 8);
			for (int j = 0; j < 8; j++) {	//해당 빈도수 자리의 빈도값++
				switch (window[j])
				{
				case 'A':
					break;
				case 'G':
					frequencyIndex = frequencyIndex + pow(4, 7 - j);
					break;
				case 'C':
					frequencyIndex = frequencyIndex + 2 * pow(4, 7 - j);
					break;
				case 'T':
					frequencyIndex = frequencyIndex + 3 * pow(4, 7 - j);
					break;
				}
			}
			tableFrequency[frequencyIndex]++;
		}
	}
}

int FrequencyTable::QuickPartition(int left, int right) {
	int pivot, intValue;
	string stringValue;

	pivot = left;
	intValue = tableFrequency[pivot];
	stringValue = tablePattern[pivot];

	do {
		do {
			left++;
		} while (tableFrequency[left] > intValue);

		do {
			right--;
		} while (tableFrequency[right] < intValue);

		if (left < right) {
			int tmpInt = tableFrequency[left];
			tableFrequency[left] = tableFrequency[right];
			tableFrequency[right] = tmpInt;

			string tmpString = tablePattern[left];
			tablePattern[left] = tablePattern[right];
			tablePattern[right] = tmpString;
		}
		else
			break;

	} while (true);

	tableFrequency[pivot] = tableFrequency[right];
	tableFrequency[right] = intValue;

	tablePattern[pivot] = tablePattern[right];
	tablePattern[right] = stringValue;
	
	return right;
}

void FrequencyTable::SortTable(int left, int right) {
	int pivot;
	if (left < right) {
		pivot = QuickPartition(left, right + 1);
		SortTable(left, pivot - 1);
		SortTable(pivot + 1, right);
	}
}

void FrequencyTable::printTable() {
	int rowLen = pow(4, 8);
	for (int i = 0; i < rowLen; i++) {
		cout << tablePattern[i] << ": " << tableFrequency[i] << endl;
	}
}


int* FrequencyTable::getTableFrequeny() {
	return tableFrequency;
}

string* FrequencyTable::getTablePattern() {
	return tablePattern;
}

//int main() {	//테이블 테스트용
//	FrequencyTable test;
//	//test.InitializeDNA();
//	test.FillFrequencyTable();
//	test.SortTable();
//	test.printTable();
//
//
//
//	string myDNA = test.DNA.getMyDNA();
//
//
//	int arr[5] = { 0 };
//	char c = 'A';
//	for (int i = 0; i < myDNA.size(); i++){
//		c = myDNA[i];
//		switch (c){
//		case 'A':
//			arr[0]++;
//			break;
//		case 'G':
//			arr[1]++;
//			break;
//		case 'C':
//			arr[2]++;
//			break;
//		case 'T':
//			arr[3]++;
//			break;
//		default:
//			arr[4]++;
//			break;
//		}
//	}	
//	
//	for (int i = 0; i < 5; i++) {
//		cout << arr[i] << endl;
//		arr[i] = 0;
//	}
//
//
//	myDNA =test.DNA.getShortRead();
//
//
//	for (int i = 0; i < myDNA.size(); i++)
//	{
//		c = myDNA[i];
//		switch (c){
//		case 'A':
//			arr[0]++;
//			break;
//		case 'G':
//			arr[1]++;
//			break;
//		case 'C':
//			arr[2]++;
//			break;
//		case 'T':
//			arr[3]++;
//			break;
//		default:
//			arr[4]++;
//			break;
//		}
//	}
//	for (int i = 0; i < 5; i++) {
//		cout << arr[i] << endl;
//		arr[i] = 0;
//	}
//}