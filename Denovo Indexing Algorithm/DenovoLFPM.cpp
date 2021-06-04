#include "DenovoLFPM.h"

DenovoLFPM::DenovoLFPM() {
	Table.InitializeDNA();	//DNA�� ���� �����ϴ� �޼���� ��Ȳ�� ���� �ּ�ó��
	Table.FillFrequencyTable();
	Table.SortTable();

	readNum = n;
	shortReadSet = Table.DNA.getShortRead();
	Table.DNA.Clear();	//shortReadSet�� DNA�� ������� ShortRead�� ������ ��ġ�Ƿ� �޸� ȿ������ ���� DNA.Clear()����
}

void DenovoLFPM::FindReadIndex(string frequencyPattern) {
	indexShortPos.clear();
	deleteShortPos.clear();
	
	istringstream ss(shortReadSet);
	string line, window;
	int rowIndex = 0;
	while (ss >> line) {	//\n�� �����ڷ� ShortRead�� ��������� ������
		IndexedRead IndexRead(line, rowIndex);

		for (int colIndex = 0; colIndex < line.size() - 7; colIndex++) {	//������ ShortRead 1���忡 ���� frequencyPattern�� �ִ��� Ž��
			window = line.substr(colIndex, 8);
			if (window == frequencyPattern)
				IndexRead.AddIndex(colIndex,t);
		}
	
		if (IndexRead.isFound) {	//������ �߰ߵ� ��쿡�� IndexRead�� ��Ͽ� �߰���
			IndexRead.CalSuPrefix(t);
			indexShortPos.push_back(IndexRead);
		}

		rowIndex = rowIndex + line.size() + 1;	//ShortRead�� ù ���� ��ġ �ֽ�ȭ
	}
}

void DenovoLFPM::MergeShortRead() {
	cout << "��Ī �˰��� ����" << endl;
	int cnt = 0;	//Ž���� �󵵼� ���̺��� �ε���
	bool isMatch = false;	//��Ī�� �Ͼ���� ����(�ݺ��� Ż�⿡ ���)
	int repeatNum=0;
	int repeatRead = 0;
	while (cnt<65000 && readNum>1){	//�󵵼� ���̺��� ��� Ž���ϰų� or ���� ShortRead�� ������ 1���� �ǰų�
		if (cnt >= 25000) {	
			if (t > 3) {
				t = 3;
				cnt = 0;
			}
			else
				break;
		}
		if (repeatNum > 5000)	//������� ���̻� �پ���� ���� ���·� 5000cnt�� ������ Ż��
			break;
		if (repeatRead == readNum)
			repeatNum++;
		else
			repeatNum = 0;
		repeatRead = readNum;
		//int a = 0;	//����׿�
		//cout << readNum << " "<<cnt<<endl;	//����׿� �ּ�ó���� �ӵ� �����

		if (Table.getTableFrequeny()[cnt] <= 1) {	//���� �󵵼� ���̺��� ����� 1�̸� Ż��(ShortRead Ž����� 1�� ���Դٴ� �ǹ��̹Ƿ� �� �̻��� Ž���� ���ǹ�)
			break;
		}

		FindReadIndex(Table.getTablePattern()[cnt++]);	//cnt������ �������� �����ͼ� �ش� �������� ������ ShortRead Ž��
		
		if (indexShortPos.size() == 0) {	//����׿�
			//cout << shortreadset;
			continue;
		}
		
		vector<IndexedRead>::iterator iter1 = indexShortPos.begin();
		vector<IndexedRead>::iterator iter2;
		for (int i = 0; i < indexShortPos.size() - 1; i++, iter1++) {	//i,j�� ���� ������ ã�� ��� ShortRead ��
			if (isMatch) {	//��Ī�� ó������ �ٽ� Ž���� ���� ���� �ʱ�ȭ
				isMatch = false;
				iter1 = indexShortPos.begin();
				//a++;	//����׿�
				//cout << a << endl;
			}
			iter2 = iter1 + 1;
			for (int j = i + 1; j < indexShortPos.size(); j++, iter2++) {
				
				
				for (int num1 = 0; num1 < indexShortPos[i].indexNum; num1++) {	//�ϳ��� ShortRead���� �������� �������� �߰߰����ϹǷ� �̰͵� ��� ��
					for (int num2 = 0; num2 < indexShortPos[j].indexNum; num2++) {
						if (indexShortPos[i].suPrefix[num1] == indexShortPos[j].suPrefix[num2]) {
							//��Ī����
							isMatch = true;
							IndexedRead NewIndexRead;
							
							//�ε��� �� �κ� ��ġ�� + �պκ��� ���� ������ �ε��� ����
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

							//�ε��� �޺κ� ��ġ�� + �޺κ��� ���� ������ �ε��� ����
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
							deleteShortPos.push_back(indexShortPos[j]);	//��Ī���������Ƿ� �ߺ� ��Ī ������ ���� ���� ShortRead�� ���� ����Ʈ�� ����
							deleteShortPos.push_back(indexShortPos[i]);

							indexShortPos.erase(iter2);	//���� ��Ͽ��� ����(�ڿ�������)
							indexShortPos.erase(iter1);

							NewIndexRead.CalSuPrefix(t);	//���ο� suPrefix ���
							NewIndexRead.rowIndex = shortReadSet.size();

							shortReadSet.append(NewIndexRead.value );	//��Ī�Ǿ� ���Ӱ� ������ NewShortRead ������ ����
							shortReadSet.append("\n");
							indexShortPos.push_back(NewIndexRead);



							readNum--;	//ShortRead ���� �Ѱ� ����
							iter1 = indexShortPos.begin();	//���ο� ShortRead�� �������Ƿ� ó������ �ٽ� ��Ī
							i = -1;	//i++�� ����� �ʱ�ȭ
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

		IndexedRead InfValue("a", INT_MAX);		//deleteShortPos�� ���� ������ ���� ������ ���� inf�� ����
		deleteShortPos.push_back(InfValue);

		SortDeletePos(0, deleteShortPos.size() - 1);	/*���� �ڿ� ��ġ�ϴ� ShortRead���� �����ؾ� ������ �ȳ��Ƿ� 
														�� ShortRead�� ���� �ε��� ��(rowIndex)�� �������� �������� ����*/

		for (int i = deleteShortPos.size()-2; i >= 0 ; i--)
			shortReadSet.erase(deleteShortPos[i].rowIndex, deleteShortPos[i].len + 1);	//��Ī�� �Ϸ�� ShortRead�� �ڿ������� ����
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
		cout << "Result.txt ���� ����" << endl;
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
	cout << "<��Ī ���>" << endl << readNum << "���� ���ڿ��� ��Ī��" << endl;
	while (ss >> line) {	//\n�� �����ڷ� ShortRead�� ��������� ������
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
		cout << num << "��: " << ((double)maxMatch / (double)M) * 100 << "%" << endl;
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
	cout << duration << "�� �ҿ�" << endl;
	test.GetAccuracy();
}