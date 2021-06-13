#include "GenerateDNA.h"


GenerateDNA::GenerateDNA() {	//������ ������ �ҷ�����
	myDNA = LoadDNA("mydna");
	shortRead = LoadDNA("shortread");
}

//�Ű������� �Է¹��� ũ�⸸ŭ�� ATGC�� �̷���� string ��ȯ
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



//myDNA�� ������� k������ shortRead�� �����ϴ� �Լ�
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

//�Ű������� �Է¹��� string�� txt�������� ����
void GenerateDNA::SaveDNA(string randomDNA, string fileName) {
	ofstream fout(fileName + ".txt");
	if (!fout) {
		cout << fileName << ".txt ���� ����" << endl;
		exit(1);
	}

	fout << randomDNA;

	fout.close();
}

//txt���Ͽ� ����� ���ڿ��� �о� string�������� ��ȯ
string GenerateDNA::LoadDNA(string fileName) {
	ifstream fin(fileName + ".txt");
	if (!fin) {
		cout << fileName << ".txt �б� ����" << endl;
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





// AGCT���� Ȯ�ο�
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