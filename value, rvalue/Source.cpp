
#include <iostream>
#include <map>
#include <algorithm>

class Intvec
{
public:
	explicit Intvec (size_t num = 0) : m_size(num), m_data(new int[m_size]) {
		log ("Constructor\n");
	}

	~Intvec() {
		log("Destructor\n");
		if (m_data) {
			delete[] m_data;
			m_data = nullptr;
		}
	}
	Intvec(const Intvec& other) : m_size(other.m_size),
		m_data(new int[m_size]) {
		log("Copy Constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}

	Intvec& operator=( Intvec&& other) noexcept{  //ссылка на rvalue
		//оператор присваивания перемещения - здесь объект конструируется 1 раз
		log("Move assigned operator");
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
		return *this;
	}

			Intvec& operator=(const Intvec & other) {
				//оператор присваивания копирования - здесь объект конструируется 2 раза ( и это требует в 2 раза больше операций)
				log("Copy assigned operator");
				Intvec tmp(other);
				std::swap(m_size, tmp.m_size);    //copy swap idioma
				std::swap(m_data, tmp.m_data);
				return *this;
			}
	
private:
	void log(const char* msg) {
		std::cout << "[" << this << "]" << msg << "\n";
 	}
	size_t m_size;
	int* m_data;
};



class A
{
public:
	void foo() const { std::cout << "A::foo() const\n"; };
	void foo() {
		std::cout << "A::foo()\n";
	}

};

A aFunc() { return A(); }
const A c_aFunc() { return A(); }


int foo() {
	return 2;
}

int globalvalue = 20;

int& bar() {  //возвраемое значение по ссылке 
return globalvalue;
}

int main() {

	//int x = 5;   //foo - lvalue, bar- rvalue
	//foo() = 2;

	//bar() = 10;

	//std::map<int, float> mymap;
	//mymap[10] = 5.6f; //lvalue - занимает идентифицированное место в памяти, operator[] внуттри класса std::map
	////который вернул ссылку на объект, который можно изменять


	//const int a = 10; // lvalue
	////a = 11;

	//int t = 1;
	//int tt = 2;
	//int res = t + tt;//operator+ ожидает rvalue, поэому 
	////неявно преобразуется в rvalue // обратного преобразвания нет

	//int arr[] = { 1,2 };
	//int* p = &arr [0];
	//*(p + 1) = 10; // явное преобразование rvalue (P+1 ) в lvalue с помощью *
	////*(P+1)- lvalue

	////lvalue в rvalue c с помощью &
	//int var = 10;
	//int* bad_addr = &(var + 1);//error для унарного рператора & требуется lvalue

	//int* addr = &var;//ok
	//&var = 40;// error с лквой стороны требуется lvalue

	////lvalue на тип Т, не я являющимся функциональным
	//// или массивом может быть реобразован в rvalue/
	////Если Т не класс, типом rvalue является 
	//// cv неспицифицированная версия типа Т.
	////rvalue является Т

	////T lvalue ->T rvalue;
	////const volitile T value ->T rvalue;

	////cv: c - const, v - volatile

	////Если Т это класс, то rvalue может сохранить 
	////cv - спицифицированность



	//aFunc().foo();
	//c_aFunc().foo(); // cv квалифицированный rvalue







	Intvec v1(20);
	Intvec v2;
	Intvec v3;


		std::cout << "assigning lvalue....\n";
		v2 = v1;
		std::cout << "ended assigning lvalue....\n";
		std::cout << "===========================\n";
		std::cout << "assigning rvalue....\n";
		v3 = Intvec(33);
		std::move(v1);// превращает rvalue в lvalue == Intvec &operator=(Intvec &&v1 )...{...}
		//v3.operator=(std::move(v1))
		std::cout << "ended assigning evalue\n";


}