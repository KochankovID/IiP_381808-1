#pragma once
#include <string>

namespace ClassTime {
	class Time
	{
	public:
		// Конструкторы -------------------------------
		Time();
		Time(const Time& time);
		Time(int hou, int min, int sec);
		Time(std::string data);

		// Методы --------------------------------------
		std::string getTimeString() const; // Запрос времени в виде строки вида: "hou.min.sec"
		void getTimeInt(int& hou, int& min, int& sec); // Запрос времени с копированием результата в переменные
		int getMin() const; // Запрос минут
		int getHou() const; // Запрос часов
		int getSec() const; // Запрос секунд

		// Перегрузки ---------------------------------
		Time& operator= (const Time& C); // Перегрузка операции присваивания
		Time operator+ (const Time& C); // Перегрузка операции сложения 
		Time operator- (const Time& C); // Перегрузка операции вычитания
		Time operator+ (const int& sec); // Перегрузка операции сложения с числом секунд
		Time operator- (const int& sec); // Перегрузка операции вычитания с числом секунд
		friend std::ostream& operator<< (std::ostream& stream, const Time& C); // Перегрузка операции вывода в поток
		friend std::istream& operator>> (std::istream& stream, Time& C); // Перегрузка операции ввода из потока

		// Перегрузка операторов сравнения ------------
		bool operator== (const Time& C) const;
		bool operator!= (const Time& C) const;
		bool operator> (const Time& C) const;
		bool operator< (const Time& C) const;
		bool operator>= (const Time& C) const;
		bool operator<= (const Time& C) const;

		// Деструктор ---------------------------------
		~Time();

		// Исключения
		struct exepOutOfRange // Выход за границы диапазона значений
		{
			std::string error; // Описание ошибки
			int amount; // Полученное значение, вызвавшее исключение
			exepOutOfRange(std::string error, int amount) : error(error), amount(amount) {}
		};

		struct exepNonNumber // Символ не является цифрой и не может быть преобразован
		{
			std::string error; // Описание ошибки
			int pos; // Позиция в строке, вызвавшая ошибку
			exepNonNumber(std::string error, int pos) : error(error), pos(pos) {}
		};

		struct exepNonAmount // Не задано значение одного из измерений времени
		{
			std::string error; // Описание ошибки
			exepNonAmount(std::string error) : error(error) {}
		};

	private:
		// Поля класса ---------------------------------
		int hou_, min_, sec_; // Единицы измерения времени

		// Методы --------------------------------------
		int strToInt(std::string data, int& sdvig); // преобразование строки в число
	};






	// Реализация inline функций
	inline void Time::getTimeInt(int & hou, int & min, int & sec)
	{
		hou = hou_;
		min = min_;
		sec = sec_;
	}

	inline int Time::getMin() const
	{
		return min_;
	}

	inline int Time::getHou() const
	{
		return hou_;
	}

	inline int Time::getSec() const
	{
		return sec_;
	}
}