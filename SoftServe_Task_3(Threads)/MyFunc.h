#pragma once
#include "AllLibraries.h"

//функци€ вывода всех папок с проектами в назначеном пути
void GetDirectories(vector<string>&, string&);

//функци€ инициализирует вектор названием файлов необходим дл€ дальнейшей обработки
void GetFiles(vector<string>&, const string&);

//проверка строк на наличие коментариев, кода и пустых строк
void CheckLines(const string&, int&, int&, int&);

//функци€, дл€ работы потока
void ThreadWork(vector<string>&, int&, int&, int&);

//функци€ сохран€юща€ данные в файл
void SaveInFileTxt(int&, int&, int&, int&, double&, string&);
