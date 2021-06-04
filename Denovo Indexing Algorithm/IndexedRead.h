#pragma once
#include "header.h"

//DenovoLFPM::FindReadIndex()�� �������� ã�� ShortRead���� ��ü�� �����ϱ� ���ؼ� ���� Ŭ����
class IndexedRead {
public:
	string value;	//��Ʈ���� ���� 
	int len;		//��Ʈ���� ����
	int rowIndex;	//�ش� ��Ʈ������ ù ������ ��ġ
	vector<int> colIndex;	//�ش� ��Ʈ���忡 �ִ� �����ϵ��� ��ġ�� ����(�� ���� ShortRead���� ���� ���� ���� ��Ī�����ϹǷ�)
	int indexNum;			//colIndex�� ����
	bool isFound;			//�������� �߰� �Ǿ����� ����(DenovoLFPM::FindReadIndex���� ����)
	vector<string> suPrefix;	/*�߰ߵ� �������� �յڷ� t��ŭ�� ���� ���̻� �κ��� ����
								���� AGCTTGCAAA���� TTGC�� �����̰� t=3�̸�
								AGC�� ���κ� AAA�� ���̺η�
								��������� AGCAAA�� �����*/

	IndexedRead();		//������� �ʱ�ȭ �����ڷ� DenovoLFPM::MergeShortRead()�� �������� ��Ī ������ ���
	IndexedRead(string value, int rowIndex);	//������� �ʱ�ȭ �����ڷ� DenovoLFPM::FindReadIndex()���� ���
	~IndexedRead();		//�Ҹ���
	void AddIndex(int index,int t );	//�������� ã���� �� �ش� �������� �ε��� �߰� �޼���
	void CalSuPrefix(int t);			//colIndex�� ������� suPrefix ����
};