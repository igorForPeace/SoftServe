#include "MyFunc.h"

void GetDirectories(vector<string>& pathHolder, string& directory)
{
	int index = 0;
	for (const auto& file : filesystem::directory_iterator(directory))
	{
		cout << index << " - " << file.path().string() << endl;
		pathHolder.push_back(file.path().string());
		index++;
	}
}

void GetFiles(vector<string>& path, const string& currentPath)
{
	for (const auto& file : filesystem::directory_iterator(currentPath))
	{
		if (filesystem::is_directory(file))
		{
			continue;
		}
		size_t lastPosOfExtension = file.path().string().rfind(".");
		if (file.path().string().substr(lastPosOfExtension, string::npos) == ".cpp" ||
			file.path().string().substr(lastPosOfExtension, string::npos) == ".hpp" ||
			file.path().string().substr(lastPosOfExtension, string::npos) == ".c" ||
			file.path().string().substr(lastPosOfExtension, string::npos) == ".h")
		{
			path.push_back(file.path().string());
		}

	}
}

void CheckLines(const string& path, int& emptyLines, int& commentLines, int& codeLines)
{
	ifstream in;
	in.open(path);
	string tempLine;
	if (in.is_open())
	{
		bool multCommentLines = false;
		while (!in.eof())
		{
			getline(in, tempLine);
			if (multCommentLines)
			{
				commentLines++;
				if (tempLine.find("*/") < tempLine.length())
				{
					multCommentLines = false;
				}
				continue;
			}
			if (tempLine == "" && !multCommentLines)
			{
				emptyLines++;
				continue;
			}
			if (tempLine.find("/*") < tempLine.length() && tempLine.find("/*") < tempLine.find("//"))
			{
				multCommentLines = true;
				for (int j = 0; j < tempLine.find("/*", 0); j++)
				{
					if (tempLine[j] == '\t' || tempLine[j] == ' ')
					{
						continue;
					}
					else
					{
						codeLines++;
						break;
					}
				}
				commentLines++;
				if (tempLine.find("*/") < tempLine.length() && tempLine.find("*/") > tempLine.find("/*"))
				{
					multCommentLines = false;
				}
				continue;
			}
			if (tempLine.find("\"") < tempLine.length() && tempLine.find("//", 0) < tempLine.length() && !multCommentLines)
			{
				if (tempLine.find("//") == tempLine.rfind("//") &&
					tempLine.find("\"") < tempLine.find("//") &&
					tempLine.rfind("\"") > tempLine.find("//"))
				{
					codeLines++;
					continue;
				}
			}
			if (tempLine.find("//", 0) < tempLine.length() && !multCommentLines)
			{
				for (int j = 0; j < tempLine.find("//", 0); j++)
				{
					if (tempLine[j] == '\t' || tempLine[j] == ' ')
					{
						continue;
					}
					else
					{
						codeLines++;
						break;
					}
				}
				commentLines++;
			}
			else
			{
				codeLines++;
			}
		}
	}
	in.close();
}

void ThreadWork(vector<string>& nameOfFiles, int& emptyLines, int& commentLines, int& codeLines)
{
	for (int i = 0; i < nameOfFiles.size(); i++)
	{
		CheckLines(nameOfFiles[i], emptyLines, commentLines, codeLines);
	}
}

void SaveInFileTxt(int& emptyLines, int& commentLines, int& codeLines, int& countOfFiles, double& time, string& nameOfDirectory)
{
	string filePath = nameOfDirectory.substr(nameOfDirectory.rfind("\\") + 1, string::npos) + "(ScanInfo).txt";
	ofstream out;
	out.open(filePath);
	if (!out.is_open())
	{
		cout << "Can not save data to file!" << endl;
		exit(0);
	}
	out << "=========================" << endl;
	out << "Name of directory with files:\t "
		<< nameOfDirectory.substr(nameOfDirectory.rfind("\\") + 1, string::npos) << endl;
	out << "Count of Empty lines\t\t = " << emptyLines << endl;
	out << "Count of comment lines\t\t = " << commentLines << endl;
	out << "Count of code lines\t\t = " << codeLines << endl;
	out << "Count of files\t\t\t = " << countOfFiles << endl;
	out << "Time spending for reading files\t = " << time << endl;
	out << "=========================" << endl;
	out.close();
}