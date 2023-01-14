//#include <fstream>
//#include <iostream>
//#include <windows.h>
//#include <string.h>
//using namespace std;
//
//int main()
//{
//
//    WIN32_FIND_DATAW wfd;
//
//    HANDLE const hFind = FindFirstFileW(L"C:\\Users\\Admin\\source\\repos\\SoftServe_Task3_(Threads)\\*", &wfd);
//    setlocale(LC_ALL, "");
//
//    if (INVALID_HANDLE_VALUE != hFind)
//    {
//        do
//        {
//            std::wcout << &wfd.cFileName[0] << std::endl;
//        } while (NULL != FindNextFileW(hFind, &wfd));
//
//        FindClose(hFind);
//    }
//
//    system("pause");
//    return 0;
//}


//#include <iostream>
//#include <vector>
//#include <filesystem>
//using namespace std;
//
////void GetFiles(vector<string>& path, const string& currentPath)
////{
////	for (const auto& file : filesystem::directory_iterator(currentPath))
////	{
////		if (filesystem::is_directory(file))
////		{
////			GetFiles(path, file.path().string());
////		}
////		else
////		{
////			size_t lastPosOfExtension = file.path().string().rfind(".");
////			if (file.path().string().substr(lastPosOfExtension, string::npos) == ".cpp"||
////				file.path().string().substr(lastPosOfExtension, string::npos) == ".hpp"||
////				file.path().string().substr(lastPosOfExtension, string::npos) == ".c"||
////				file.path().string().substr(lastPosOfExtension, string::npos) == ".h")
////			{
////				path.push_back(file.path().string());
////			}
////		}
////	}
////}
//
//void GetFiles(vector<string>& path, const string& currentPath)
//{
//	for (const auto& file : filesystem::directory_iterator(currentPath))
//	{
//		if (filesystem::is_directory(file))
//		{
//			continue;
//		}
//		size_t lastPosOfExtension = file.path().string().rfind(".");
//		if (file.path().string().substr(lastPosOfExtension, string::npos) == ".cpp" ||
//			file.path().string().substr(lastPosOfExtension, string::npos) == ".hpp" ||
//			file.path().string().substr(lastPosOfExtension, string::npos) == ".c" ||
//			file.path().string().substr(lastPosOfExtension, string::npos) == ".h")
//		{
//			path.push_back(file.path().string());
//		}
//		
//	}
//}
//
//
//
//int main()
//{
//	string path = "C:\\Users\\Admin\\source\\repos";
//	vector<string> directories;
//	cout << "Here is your directories:\n\n";
//	GetDirectories(directories, path);
//
//	cout << "\n size of directories: " << directories.size() << endl;
//
//	int indexOfDirectory;
//	cout << "Enter the number of directory: ";
//	while (true)
//	{
//		if (cin >> indexOfDirectory)
//		{
//			if (indexOfDirectory>=directories.size())
//			{
//				cout << "Please enter correct number: ";
//			}
//			else
//			{
//				break;
//			}		
//		}
//		else
//		{
//			cout << "Enter a number: ";
//		}
//		cin.clear();
//		cin.get();
//	}
//
//	
//	vector<string> files;
//	GetFiles(files, directories[indexOfDirectory]);
//	for (int i = 0; i < files.size(); i++)
//	{
//		cout << files[i] << endl;
//	}
//
//	cout << "\nSize of vector with files: " << files.size() << endl;
//	return 0;
//
//	//int a;
//	//cout << "Enter a number: ";
//	///*cin >> a;*/
//	//while (true)
//	//{
//	//	if (cin>>a)
//	//	{
//	//		break;
//	//	}
//	//	else
//	//	{
//	//		cout << "Enter a number: ";
//	//	}
//	//	cin.clear();
//	//	cin.get();
//	//}
//	//cout << "you entered: " << a << endl;
//	return 0;
//}