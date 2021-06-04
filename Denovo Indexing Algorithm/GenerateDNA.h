#pragma once
#include "header.h"


class GenerateDNA {
private:
	string myDNA, shortRead;	//DNA, ShortRead ����

	void SaveDNA(string randomDNA, string fileName);	//fileName.txt�� �ش� randomDNA ���� �޼���
	string LoadDNA(string fileName);					//fileName.txt�� ���� ��ȯ �޼���
public:
	GenerateDNA();		//������ ����� DNA, ShortRead �о ���� ������
	void MkDNA();		//���� ����� DNA���� ���ο� DNA ����� �޼���
	void MkShortRead();	//���� ����� ShortRead���� ���ο� ShortRead ����� �޼���
	string getMyDNA();	//myDNA��ȯ �޼���
	string getShortRead();	//ShortRead ��ȯ �޼���
	void Clear();		//�޸� ������ �Ƴ�������  myDNA, shortRead ���� �޼���
};
