#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//Returns the number of items in the list / возврат размера списка 
int StringListSize(char*** list)
{
	if (*list != nullptr) //если список не пустой
	{
		return _msize(*list) / sizeof(char*);
	}
	return 0;
}

//Destroy list and set pointer to NULL / высвобождение памяти 
void StringListDestroy(char*** list)
{
	if (*list != nullptr)
	{
		int size = StringListSize(list);
		for (int i = 0; i < size; i++)
		{
			free((*list)[i]);
		}
		free(*list);
		*list = nullptr;
	}
}

//Initializes list / инициализация списка
void StringListInit(char*** list)
{
	if (StringListSize(list))
	{
		StringListDestroy(list);
	}
	int temp_size;  //переменная для хранения размера списка
	cout << "Enter a number of strings you need: ";
	cin >> temp_size;
	cin.get();
	const int BUFF_SIZE = 200;
	*list = (char**)malloc(temp_size*sizeof(char*)); //выделяем память для нашего списка 
	char buff[BUFF_SIZE]; //создаем отдельный массив char для хранения временной строки

	for (int i = 0; i < temp_size; i++)
	{
		cout << "Enter the string #" << i + 1 << ": ";
		cin.getline(buff, BUFF_SIZE); 
		(*list)[i] = (char*)malloc(strlen(buff) * sizeof(char)+1);
		strcpy_s((*list)[i], strlen(buff) + 1, buff);
	}
}



//Inserts value at the end of the list / добавление слова в конец списка
void StringListAdd(char*** list, const char* str)
{
	int size = StringListSize(list);
	char** temp_list = (char**)realloc(*list, sizeof(char*)*(size + 1)); //создаем временный объект 
	if (temp_list!=NULL)
	{
		*list = temp_list;
		(*list)[size] = (char*)malloc(sizeof(char)*strlen(str) + 1);
		strcpy_s((*list)[size], strlen(str) + 1, str);
	}
	else
	{
		StringListDestroy(list);
		cout << "allocation error" << endl;
		exit(1);
	}
}

//Returns the index position of the first occurrence of str in the list / возврат индекса первого вхождения переданой строки
int StringListIndexOf(char*** list, const char* str)
{
	if (list != nullptr)
	{
		int size = StringListSize(list);
		for (int i = 0; i < size; i++)
		{
			if (strcmp((*list)[i], str) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}

//вывод всех строк
void ShowAllStrings(char*** list)
{
	int size = StringListSize(list);
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Your strings #" << i + 1 << ": " << (*list)[i] << endl;
	}
}

//function for sorting
int comp(const void* str1, const void* str2)
{
	return strcmp(*(char**)str1, *(char**)str2);
}

//Sorts the list of strings in ascending order
void StringListSort(char*** list)
{
	int size = StringListSize(list);
	if (size <= 1) return;
	qsort(*list, size, sizeof(char*), comp);
}

//counts the number of words needed
int CountOfStr(char*** list, const char* str)
{
	int count = 0;
	int size = StringListSize(list);
	if (size == 0) return count;
	for (int i = 0; i < size; i++)
	{
		if (strcmp((*list)[i], str) == 0)
		{
			count++;
		}
	}
	return count;
}

//Removes all occurrences of str in the list
void StringListRemove(char*** list, const char* str)
{
	int count_of_words = CountOfStr(list, str);
	if (!count_of_words)
	{
		cout << "There are no your words in the list!" << endl;
		return;
	}
	int size = StringListSize(list);
	int new_size = size - count_of_words;
	char** temp = (char**)malloc(sizeof(char*) * new_size);
	for (int i = 0; i < new_size; i++)
	{
		temp[i] = (char*)malloc(sizeof(char) * 100);
	}
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		if (strcmp((*list)[i], str) == 0)
		{
			continue;
		}
		strcpy_s(temp[j], strlen((*list)[i]) + 1, (*list)[i]);
		j++;
	}
	StringListDestroy(list);
	*list = temp;
}

// Removes duplicate entries from the list.
void StringListRemoveDuplicates(char*** list)
{
	int old_size = StringListSize(list);
	if (old_size < 2) return; //если в списке одно слово или список пуст - ничего не делаем
	StringListSort(list);
	char** temp = (char**)malloc(sizeof(char*)); 
	int j = 0;
	int new_size = 1;
	temp[j] = (char*)malloc(sizeof(char) * (strlen((*list)[0]) + 1));
	strcpy_s(temp[j], strlen((*list)[0]) + 1, (*list)[0]);
	for (int i = 1; i < old_size; i++)
	{
		if (strcmp(temp[j], (*list)[i])==0)
		{
			continue;
		}
		temp = (char**)realloc(temp, sizeof(char*) * (++new_size));
		if (temp == NULL)
		{
			StringListDestroy(list);
			cout << "allocation error" << endl;
			exit(1);
		}
		j++;
		temp[j] = (char*)malloc(sizeof(char) * (strlen((*list)[i]) + 1));
		strcpy_s(temp[j], strlen((*list)[i]) + 1, (*list)[i]);
	}
	StringListDestroy(list);
	*list = temp;
}


// Replaces every occurrence of the before, in each of the string lists's strings, with after. 
void StringListReplaceInStrings(char*** list, char* before, char* after)
{
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		if (strcmp((*list)[i], before)==0)
		{
			strcpy_s((*list)[i], strlen(after) + 1, after);
		}
	}
}

int main()
{
	
	return 0;

	//TESTS

	//char** words = nullptr;

	//
	//cout << StringListIndexOf(&words, "Hello my new List!") << endl;

	//cout << "List size: " << StringListSize(&words) << endl;


	//StringListDestroy(&words);

	//StringListInit(&words);
	//cout << "before replacing:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//StringListRemoveDuplicates(&words);

	//cout << "After raplacing:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//StringListRemoveDuplicates(&words);

	//cout << "After removing dublicates:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//cout << "Enter the word you want to delete in list: ";
	//char buff[100];
	//cin.getline(buff, 100);
	//StringListRemove(&words, buff);
	//cout << "After delete:\n";
	//
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #"<<i+1<<": "<<words[i] << endl;
	//}

	//cout << "Index of abc before sorting: " << StringListIndexOf(&words, "abc");


	//StringListSort(&words);
	//cout << "After sorting:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//cout << "Index of abc before sorting: " << StringListIndexOf(&words, "abc");

	//StringListAdd(&words, "cbabcd");
	//cout << "After adding 1 word without sorting:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}
	//StringListSort(&words);
	//cout << "After adding 1 word with sorting:\n";
	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}


	//cout << "Your string index is: " << StringListIndexOf(&words, "hello 1") << endl;
	//cout << "Your string index is: " << StringListIndexOf(&words, "uoy") << endl;
	//cout << "Size of your list is: " << StringListSize(&words) << endl;



	//StringListDestroy(&words);

	/////////////

	//StringListInit(&words);

	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//cout << "Size of your list is: " << StringListSize(&words) << endl;

	////StringListAdd(&words, "Another new hello world");

	//for (int i = 0; i < 5; i++)
	//{
	//	char* buff = (char*)malloc(sizeof(char*) * 100);
	//	cout << "Enter string: ";
	//	cin.getline(buff, 100);
	//	StringListAdd(&words, buff);
	//	free(buff);
	//}

	//for (int i = 0; i < StringListSize(&words); i++)
	//{
	//	cout << "Your strings #" << i + 1 << ": " << words[i] << endl;
	//}

	//cout << "Size of your list is: " << StringListSize(&words) << endl;

	//StringListDestroy(&words);

	//char** list = nullptr;
	//StringListInit(&list);
	//cout << endl;
	//for (int i = 0; i < StringListSize(&list); i++)
	//{
	//	cout << "Your new list of string #" << i + 1 << ": " << list[i] << endl;
	//}

	//StringListDestroy(&list);*/
	
}