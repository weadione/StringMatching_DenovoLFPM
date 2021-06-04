#pragma once
#include "header.h"
#include "GenerateDNA.h"

class FrequencyTable {
private:

	string* tablePattern;	//4^8���� ���� 8¥�� ������ ��� AGCT�� �迭 (���� ������)
	int* tableFrequency;	//�� AGCT�迭�� ���Ұ� shortRead���� �����ϴ� �󵵼�
	
	int QuickPartition(int left, int right);	//����Ʈ ��Ƽ�� �޼���(��������)

public:
	GenerateDNA DNA;	//dna ��ü(DNA, ShortRead ���� ����)

	FrequencyTable();		
	void InitializeDNA();			//���ο� DNA�� shortRead ����
	void FillFrequencyTable();		//shortRead �󵵼� ����
	void SortTable(int left=0, int right = pow(4, 8) - 1);	//����Ʈ�� ����� ���̺��� ������������ �����ϴ� �޼���
	void printTable();				//����׿� ���̺� ��� �޼���
	int* getTableFrequeny();		//tableFrequency�� ��ȯ�ϴ� �޼���
	string* getTablePattern();		//tablePattern�� ��ȯ�ϴ� �޼���
};