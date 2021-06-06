#pragma once
#include "header.h"
#include"FrequencyTable.h"
#include "IndexedRead.h"

class DenovoMFPM {
private:
	FrequencyTable Table;	//�󵵼� ���̺� ��ü
	vector<IndexedRead> indexShortPos;	//���� �������� ������ ShortRead���� ���
	vector<IndexedRead> deleteShortPos;	//��Ī�� �Ǿ �����ؾ��� ShortRead���� ���
	mutex m;

	string shortReadSet;		//ShortRead�� ��ü ���ڿ�
	int readNum;			//�����ִ� ShortReadd�� ����
	int t = 5;	/*ã�� �ε��� �յڷ� Ž���� ����
				(ex. ���� t�� 4�̸� 8���� ��Ī�� ���� �յڷ� ���� 4���� �� ����
				�� 16���� ���ƾ� �̾��� read��� �Ǻ�)*/

	int QuickPartition(int left, int right);	//����Ʈ ��Ƽ�� �޼���(��������)
	void SortDeletePos(int left, int right);	//����Ʈ�� ����� deleteShortPos�� ������������ �����ϴ� �޼���

public:
	DenovoMFPM();	//Table��ü�� �޼��� ���� �� ������� �ʱ�ȭ ������
	void FindReadIndex(string frequencyPattern);	//frequencyPattern�� ������ �ִ� ShortRead���� Ž���ؼ� indexShortPos�� �߰�
	void ThreadFindReadIndex(string frequencyPattern, string shortRead, int rowIndex, mutex& m);	//��Ƽ�������� ���� �Լ�
	void MergeShortRead();	//��Ī �˰���(�ٽɾ˰���)
	void print();	//Result.txt���Ͽ� �������� ���� DNA ����
	void GetAccuracy();		//��Ȯ�� ��� �� ���
};