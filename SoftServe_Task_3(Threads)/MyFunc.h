#pragma once
#include "AllLibraries.h"

//������� ������ ���� ����� � ��������� � ���������� ����
void GetDirectories(vector<string>&, string&);

//������� �������������� ������ ��������� ������ ��������� ��� ���������� ���������
void GetFiles(vector<string>&, const string&);

//�������� ����� �� ������� �����������, ���� � ������ �����
void CheckLines(const string&, int&, int&, int&);

//�������, ��� ������ ������
void ThreadWork(vector<string>&, int&, int&, int&);

//������� ����������� ������ � ����
void SaveInFileTxt(int&, int&, int&, int&, double&, string&);
