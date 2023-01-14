#include <iostream>
using namespace std;

//объединение с возможными стандартными типами
union Type
{
	char c;
	short int s_i;
	int i;
	long int l_i;
	long long int ll_i;
	float f;
	double d;
	bool b;
	char mes[10];
};

//класс исключение
class ExceptionType: public exception
{
private:
	string error;
	
public:
	ExceptionType(string er): error(er) {}

	const char* what() const noexcept
	{
		return error.c_str();
	}
};

//пользовательский тип данныз для хранения одновременно одной переменной разных типов
class AnyType
{
private:
	Type t;
	short current_type;

	//метод инициализации нашего объекта
	template<typename T>
	void InitType(T value)
	{
		if (typeid(value).name() == typeid(t.c).name())
		{
			t.c = value;
			current_type = 1;
		}
		else if (typeid(value).name() == typeid(t.s_i).name())
		{
			t.s_i = value;
			current_type = 2;
		}
		else if (typeid(value).name() == typeid(t.i).name())
		{
			t.i = value;
			current_type = 3;
		}
		else if (typeid(value).name() == typeid(t.l_i).name())
		{
			t.l_i = value;
			current_type = 4;
		}
		else if (typeid(value).name() == typeid(t.ll_i).name())
		{
			t.ll_i = value;
			current_type = 5;
		}
		else if (typeid(value).name() == typeid(t.f).name())
		{
			t.f = value;
			current_type = 6;
		}
		else if (typeid(value).name() == typeid(t.d).name())
		{
			t.d = value;
			current_type = 7;
		}
		else if (typeid(value).name() == typeid(t.b).name())
		{
			t.b = value;
			current_type = 8;
		}
	}

public:
	//конструктор с параметрами
	template<typename T>
	AnyType(T value)
	{
		this->InitType(value);
	}

	//конструктор по умолчанию
	AnyType()
	{
		strcpy_s(t.mes, strlen("no data") + 1, "no data");
		current_type = 0;
	}

	//конструктор копирования
	AnyType(const AnyType& other)
	{
		this->t = other.t;
		this->current_type = other.current_type;
	}

	//конструктор перемещения
	AnyType(AnyType&& other) noexcept
	{
		this->t = other.t;
		this->current_type = other.current_type;
		other.DestroyObj();
	}

	AnyType& operator=(AnyType&& other) noexcept
	{
		if (this!=&other)
		{
			this->t = other.t;
			this->current_type = other.current_type;
			other.DestroyObj();
		}	
		return *this;
	}

	//перегрузка оператора копирования присваиванием для пользовательского типа
	AnyType& operator=(const AnyType& other)
	{
		if (this == &other)
		{
			return *this;
		}
		this->t = other.t;
		this->current_type = other.current_type;
		return *this;
	}

	//перегрузка оператора присваивания для стандартных типов
	template<typename T>
	AnyType& operator=(const T& value)
	{
		this->InitType(value);
		return *this;
	}

	//метод swap
	void Swap(AnyType& other)
	{
		AnyType temp = *this;
		*this = other;
		other = temp;
	}

	const char* Type() const
	{
		if (this->current_type == 1) return typeid(this->t.c).name();
		else if (this->current_type == 2) return typeid(this->t.s_i).name();
		else if (this->current_type == 3) return typeid(this->t.i).name();
		else if (this->current_type == 4) return typeid(this->t.l_i).name();
		else if (this->current_type == 5) return typeid(this->t.ll_i).name();
		else if (this->current_type == 6) return typeid(this->t.f).name();
		else if (this->current_type == 7) return typeid(this->t.d).name();
		else if (this->current_type == 8) return typeid(this->t.b).name();
		else if (this->current_type == 0) return "no type";
	}

	AnyType& DestroyObj()
	{
		strcpy_s(this->t.mes, strlen("no data") + 1, "no data");
		this->current_type = 0;
		return *this;
	}

	//метод вывода информации о типе на экран
	void ShowType() const
	{
		switch (this->current_type)
		{
		case 1:
			cout << "your type is " << typeid(t.c).name() << ", value: " << t.c << " or " << int(t.c) << endl;
			break;
		case 2:
			cout << "your type is " << typeid(t.s_i).name() << ", value: " << t.s_i << endl;
			break;
		case 3:
			cout << "your type is " << typeid(t.i).name() << ", value: " << t.i << endl;
			break;
		case 4:
			cout << "your type is " << typeid(t.l_i).name() << ", value: " << t.l_i << endl;
			break;
		case 5:
			cout << "your type is " << typeid(t.ll_i).name() << ", value: " << t.ll_i << endl;
			break;
		case 6:
			cout << "your type is " << typeid(t.f).name() << ", value: " << t.f << endl;
			break;
		case 7:
			cout << "your type is " << typeid(t.d).name() << ", value: " << t.d << endl;
			break;
		case 8:
			cout << "your type is " << typeid(t.b).name() << ", value: " << boolalpha << t.b << endl;
			break;
		case 0:
			cout << t.mes << endl;
			break;
		default:
			break;
		}
	}

	char ToChar() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if(this->current_type == 2 && this->t.s_i >= -128 && this->t.s_i <= 127)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3 && this->t.i >= -128 && this->t.i <= 127)
		{
			return this->t.i;
		}
		else if (this->current_type == 4 && this->t.l_i >= -128 && this->t.l_i <= 127)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5 && this->t.ll_i >= -128 && this->t.ll_i <= 127)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 6 && this->t.f >= -128 && this->t.f <= 127)
		{
			int temp = this->t.f;
			if (temp == this->t.f)
			{
				return this->t.f;
			}
			throw ExceptionType("can not convert to char!");
		}
		else if (this->current_type == 7 && this->t.d >= -128 && this->t.d <= 127)
		{
			int temp = this->t.d;
			if (temp == this->t.d)
			{
				return this->t.d;
			}
			throw ExceptionType("can not convert to char!");
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to char!");
	}

	short ToShort() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3 && this->t.i>=SHRT_MIN &&this->t.i <=SHRT_MAX)
		{
			return this->t.i;
		}
		else if (this->current_type == 4 && this->t.l_i >= SHRT_MIN && this->t.l_i <= SHRT_MAX)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5 && this->t.ll_i >= SHRT_MIN && this->t.ll_i <= SHRT_MAX)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6 && this->t.f >= SHRT_MIN && this->t.f <= SHRT_MAX)
		{
			int temp = this->t.f;
			if (temp == this->t.f)
			{
				return this->t.f;
			}
			throw ExceptionType("can not convert to short!");
		}
		else if (this->current_type == 7 && this->t.d >= SHRT_MIN && this->t.d <= SHRT_MAX)
		{
			int temp = this->t.d;
			if (temp == this->t.d)
			{
				return this->t.d;
			}
			throw ExceptionType("can not convert to short!");
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to short!");
	}

	int ToInt() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4 && this->t.l_i >= INT_MIN && this->t.l_i <= INT_MAX)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5 && this->t.ll_i >= INT_MIN && this->t.ll_i <= INT_MAX)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6 && this->t.f >= INT_MIN && this->t.f <= INT_MAX)
		{
			int temp = this->t.f;
			if (temp == this->t.f)
			{
				return this->t.f;
			}
			throw ExceptionType("can not convert to int!");
		}
		else if (this->current_type == 7 && this->t.d >= INT_MIN && this->t.d <= INT_MAX)
		{
			int temp = this->t.d;
			if (temp == this->t.d)
			{
				return this->t.d;
			}
			throw ExceptionType("can not convert to int!");
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to int!");
	}

	long ToLong() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5 && this->t.ll_i >= LONG_MIN && this->t.ll_i <= LONG_MAX)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6 && this->t.f >= LONG_MIN && this->t.f <= LONG_MAX)
		{
			int temp = this->t.f;
			if (temp == this->t.f)
			{
				return this->t.f;
			}
			throw ExceptionType("can not convert to long!");
		}
		else if (this->current_type == 7 && this->t.d >= LONG_MIN && this->t.d <= LONG_MAX)
		{
			int temp = this->t.d;
			if (temp == this->t.d)
			{
				return this->t.d;
			}
			throw ExceptionType("can not convert to long!");
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to long!");
	}

	long long ToLongLong() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6 && this->t.f >= LLONG_MIN && this->t.f <= LLONG_MAX)
		{
			int temp = this->t.f;
			if (temp == this->t.f)
			{
				return this->t.f;
			}
			throw ExceptionType("can not convert to long long!");
		}
		else if (this->current_type == 7 && this->t.d >= LLONG_MIN && this->t.d <= LLONG_MAX)
		{
			int temp = this->t.d;
			if (temp == this->t.d)
			{
				return this->t.d;
			}
			throw ExceptionType("can not convert to long long!");
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to long long!");
	}

	float ToFloat() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6)
		{
			return this->t.f;
		}
		else if (this->current_type == 7)
		{
			return this->t.d;
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to float!");
	}
	
	double ToDouble() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6)
		{
			return this->t.f;
		}
		else if (this->current_type == 7)
		{
			return this->t.d;
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to double!");
	}
	

	bool ToBool() const
	{
		if (this->current_type == 1)
		{
			return this->t.c;
		}
		else if (this->current_type == 2)
		{
			return this->t.s_i;
		}
		else if (this->current_type == 3)
		{
			return this->t.i;
		}
		else if (this->current_type == 4)
		{
			return this->t.l_i;
		}
		else if (this->current_type == 5)
		{
			return this->t.ll_i;
		}
		else if (this->current_type == 6)
		{
			return this->t.f;
		}
		else if (this->current_type == 7 )
		{
			return this->t.d;
		}
		else if (this->current_type == 8)
		{
			return this->t.b;
		}
		throw ExceptionType("can not convert to bool!");
	}
};


int main()
{

	AnyType a;
	
	double b;
	
	try
	{
		b = a.ToDouble();
		cout<< b << " , type is " << typeid(b).name() << endl;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	a = 1;
	
	try
	{
		b = a.ToDouble();
		cout << b << " , type is " << typeid(b).name() << endl;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
	//AnyType c;
	//c.ShowType();

	/*AnyType c = double(127);
	c.ShowType();
	try
	{
		int a = c.ToShort();
		cout << a << endl;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}*/

	
	

	
}