#include "GenerateDNA.h"


GenerateDNA::GenerateDNA() {	//기존의 데이터 불러오기
	myDNA = LoadDNA("mydna");
	shortRead = LoadDNA("shortread");
}

//매개변수로 입력받은 크기만큼의 ATGC로 이루어진 string 반환
void GenerateDNA::MkDNA() {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 3);

	myDNA = "";

	for (int i = 0; i < M; i++) {
		switch (dis(gen)) {
		case 0:
			myDNA.append("A");
			break;
		case 1:
			myDNA.append("T");
			break;
		case 2:
			myDNA.append("G");
			break;
		case 3:
			myDNA.append("C");
			break;
		default:
			break;
		}
	}


	SaveDNA(myDNA, "mydna");
}



//myDNA를 기반으로 k길이의 shortRead를 생성하는 함수
void GenerateDNA::MkShortRead() {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, M-k);
	shortRead = "";
	string tmp = "";
	for (int i = 0; i < n; i++) {
		shortRead.append(myDNA.substr(dis(gen), k)+"\n");
	}

	SaveDNA(shortRead, "shortread");

}

//매개변수로 입력받은 string을 txt형식으로 저장
void GenerateDNA::SaveDNA(string randomDNA, string fileName) {
	ofstream fout(fileName + ".txt");
	if (!fout) {
		cout << fileName << ".txt 쓰기 실패" << endl;
		exit(1);
	}

	fout << randomDNA;

	fout.close();
}

//txt파일에 저장된 문자열을 읽어 string형식으로 반환
string GenerateDNA::LoadDNA(string fileName) {
	ifstream fin(fileName + ".txt");
	if (!fin) {
		cout << fileName << ".txt 읽기 실패" << endl;
		return "";
	}

	string fileDNA, tmp;
	getline(fin, tmp);
	fileDNA.append(tmp);
	while (!fin.eof()) {
		getline(fin,tmp);
		fileDNA.append("\n" + tmp);
	}


	fin.close();

	return fileDNA;
}

string GenerateDNA::getMyDNA() {
	return myDNA;
}

string GenerateDNA::getShortRead() {
	return shortRead;
}

void GenerateDNA::Clear() {
	shortRead = "";
}





// AGCT분포 확인용
//int main() {
//	GenerateDNA dna;
//	dna.MkDNA(M);
//	dna.MkShortRead();
//	string myDNA = dna.getMyDNA();
//
//
//	int arr[5] = { 0 };
//	char c = "A";
//	for (int i = 0; i < myDNA.size(); i++)
//	{
//		c = myDNA[i];
//		switch (c)
//		{
//		case "A":
//			arr[0]++;
//			break;
//		case "G":
//			arr[1]++;
//			break;
//		case "C":
//			arr[2]++;
//			break;
//		case "T":
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
//	myDNA = dna.getShortRead();
//
//
//	for (int i = 0; i < myDNA.size(); i++)
//	{
//		c = myDNA[i];
//		switch (c)
//		{
//		case "A":
//			arr[0]++;
//			break;
//		case "G":
//			arr[1]++;
//			break;
//		case "C":
//			arr[2]++;
//			break;
//		case "T":
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
//
//}