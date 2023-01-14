#include "AllLibraries.h"
#include "MyFunc.h"

int main()
{
	setlocale(LC_ALL, "ru");
	string path = "C:\\Users\\Admin\\source\\repos";  //�������� ����, ��� ����� ����� � ���������
	vector<string> directories;						  //������ �������� ����� � ���������
	cout << "Here is your directories:\n\n";
	GetDirectories(directories, path);          //������������� ������� ���������� �����
	cout << "\nSize of directories: " << directories.size() << endl;
	int indexOfDirectory;                            //����� ����������� ��� �����
	cout << "Enter the number of directory: ";
	while (true)
	{
		if (cin >> indexOfDirectory)  //�������� �� ����������� ����� ������
		{
			if (indexOfDirectory >= directories.size())
			{
				cout << "Please enter correct number: ";
			}
			else
			{
				break;
			}
		}
		else
		{
			cout << "Enter a numeric number (not char or string): ";
		}
		cin.clear();
		cin.get();
	}
	
	vector<string> files;  //�������� � ������������� ������� � ���������� ������ ��� ������
	GetFiles(files, directories[indexOfDirectory]);
	for (int i = 0; i < files.size(); i++)
	{
		cout << files[i] << endl;
	}

	//��������� ������ � ���������� ������ �� ��� �������, ���� �������� �� ��������� � �����, ������ �������������� � �����
	vector<string> firstPartOfFiles(files.begin(), files.begin() + files.size() / 2);
	vector<string> secondPartOfFiles(files.begin() + files.size() / 2, files.end());
	clock_t start = clock();

	int countOfEmptyLines = 0;
	int countOfCommentLines = 0;
	int countOfCodeLines = 0;

	thread th(ThreadWork, ref(secondPartOfFiles), ref(countOfEmptyLines), ref(countOfCommentLines), ref(countOfCodeLines));

	for (int i = 0; i < firstPartOfFiles.size(); i++)
	{
		CheckLines(firstPartOfFiles[i], countOfEmptyLines, countOfCommentLines, countOfCodeLines);
	}

	th.join();

	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	int countOfFiles = files.size();
	cout << "\nEnd of program" << endl;
	cout << "Name of directory with files:\t " 
		<< directories[indexOfDirectory].substr(directories[indexOfDirectory].rfind("\\")+1, string::npos) << endl;
	cout << "Count of Empty lines\t\t = " << countOfEmptyLines << endl;
	cout << "Count of comment lines\t\t = " << countOfCommentLines << endl;
	cout << "Count of code lines\t\t = " << countOfCodeLines << endl;
	cout << "Count of files\t\t\t = " << countOfFiles << endl;
	cout << "Time spending for reading files\t = " << time << endl;
	
	//���������� ���������� � ����
	SaveInFileTxt(countOfEmptyLines, countOfCommentLines, countOfCodeLines, countOfFiles, time, directories[indexOfDirectory]);
	return 0;
}