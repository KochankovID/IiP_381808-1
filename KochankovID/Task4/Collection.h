#pragma once
#include <memory>
#include <iostream>

template<typename T>
class Collection
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор
	explicit Collection(const int& Count_);

	// Конструктор по умолчанию
	Collection();

	// Конструктор копирования
	Collection(const Collection& copy);

	// Методы класса ---------------------------------------------------------
	// Получение количества элементов коллекции
	const int& Count() const { return count; };

	// Поиск индекса элемента
	int Find(T& element) const;

	// Добавление элемента в коллекцию
	void Add(const T& element);

	// Добавление элемента в коллекцию
	void AddAt(const T& element, const int& pos);

	// Удаление элемента из коллекции 
	void Remove(T& element); 

	// Удаление элемента из коллекции по индексу
	void RemoveAt(const int& index);

	// Возвращает количество одинаковых элементов
	int Koll(const T& element) const;

	// Возвращает массив элементов типа Т
	T* AsArray() { return sbornik._Myptr(); };

	// Перегрузка операторов -------------------------------------------------
	// Перегрузка оператора индексирования
	T& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const T& operator[](const int& i) const;

	// Перегрузка оператора присваивания
	Collection<T>* operator= (const Collection<T>& copy);
	
	// Перегрузка операции вывода в поток
	template <typename T1> friend std::ostream& operator<< (std::ostream& stream, const Collection<T1>& C);

	// Перегрузка операции ввода из потока
	template <typename T1> friend std::istream& operator>> (std::istream& stream, Collection<T1>& C); 

	// Деструктор ------------------------------------------------------------
	~Collection<T>();

private:
	// Поля класса -----------------------------------------------------------
	static const int BufPlace = 20; // Размер заранее выделяемого буфера
	int count; // Количество элементов в колекции
	int bufSize; // Размер буфера динамического массива указателей
	std::unique_ptr<T[]> sbornik; // "Умный" указатель на динамический массив 
	//(применем чтобы избежать утечек памяти при вызове исключения из конструктора Т)
	void IsInRange(const int& i) const; // Проверка на вхождение в диапазон
	void bufAdd(); // Увеличение буфера коллекции
	void buffree(); // Уменьшение буфера коллекции

};
// Объявление "Инлайн" функций

template<typename T>
Collection<T>::Collection(const int & Count_) :
	count(Count_),
	bufSize(count + BufPlace),
	sbornik(new T[bufSize])
{
}

template<typename T>
Collection<T>::Collection() :
	count(0),
	bufSize(BufPlace),
	sbornik(new T[BufPlace])
{
}

template<typename T>
Collection<T>::Collection(const Collection & copy): count(copy.count), 
	bufSize(copy.bufSize),
	sbornik(new T[bufSize])
{
	for (int i = 0; i < copy.Count(); i++) {
		sbornik[i] = copy.sbornik[i];
	}
}

template<typename T>
int Collection<T>::Find(T & element) const
{
	for (int i = 0; i < count; i++) {
		if (sbornik[i] == element) {
			return i;
		}
	}
	return -1;
}


template<typename T>
void Collection<T>::Add(const T & element)
{
	if (count == bufSize) {
		bufAdd();
	}
	sbornik[count] = element;
	count++;
}

template<typename T>
inline void Collection<T>::AddAt(const T & element, const int & pos)
{
	if (count == bufSize) {
		bufAdd();
	}
	for (int i = count; i > pos; i--) {
		sbornik[i] = sbornik[i - 1];
	}
	count++;
	sbornik[pos] = element;
}

template<typename T>
void Collection<T>::Remove(T & element)
{
	int pos = Find(element);
	for (int i = pos; i < count - 1; i++) {
		sbornik[i] = sbornik[i + 1];
	}
	count--;
	if ((bufSize - count) >= (2 * BufPlace)) {
		buffree();
	}
}

template<typename T>
inline void Collection<T>::RemoveAt(const int & index)
{
	for (int i = index; i < count - 1; i++) {
		sbornik[i] = sbornik[i + 1];
	}
	count--;
	if ((bufSize - count) >= (2 * BufPlace)) {
		buffree();
	}
}

template<typename T>
int Collection<T>::Koll(const T & element) const
{
	int kol = 0;
	for (int i = 0; i < count; i++) {
		if (sbornik[i] == element) {
			kol++;
		}
	}
	return kol;
}

template<typename T>
T & Collection<T>::operator[](const int & i)
{
	IsInRange(i);
	return sbornik[i];
}

template<typename T>
const T & Collection<T>::operator[](const int & i) const
{
	IsInRange(i);
	return sbornik[i];
}

template<typename T>
Collection<T>* Collection<T>::operator=(const Collection<T>& copy)
{
	count = copy.count;
	bufSize = copy.bufSize;
	sbornik.reset(new T[bufSize]);
	for (int i = 0; i < count; i++) {
		sbornik[i] = copy.sbornik[i];
	}
	return this;
}

template<typename T>
Collection<T>::~Collection()
{
	sbornik.reset();
}

template<typename T>
void Collection<T>::IsInRange(const int & i) const
{
	if ((i < 0) || (i >= count)) {
		throw std::out_of_range("Индекс находится вне границ массива!");
	}
}

template<typename T>
void Collection<T>::bufAdd()
{
	bufSize += BufPlace;
	std::unique_ptr<T[]> copy(new T[bufSize]);

	for (int i = 0; i < count; i++) {
		copy[i] = sbornik[i];
	}
	sbornik = std::move(copy);
}

template<typename T>
inline void Collection<T>::buffree()
{
	bufSize -= BufPlace;
	std::unique_ptr<T[]> copy(new T[bufSize]);

	for (int i = 0; i < count; i++) {
		copy[i] = sbornik[i];
	}
	sbornik = std::move(copy);
}


template<typename T>
std::ostream & operator<<(std::ostream & stream, const Collection<T> & C)
{
	stream << C.count << ' ' << C.bufSize << std::endl;
	for (int i = 0; i < C.count; i++) {
		stream << C.sbornik[i] << std::endl;
	}
	return stream;
}

template<typename T>
std::istream & operator>>(std::istream & stream, Collection<T> & C)
{
	stream >> C.count;
	stream >> C.bufSize;
	C.sbornik.reset(new T[C.bufSize]);
	for (int i = 0; i < C.count; i++) {
		stream >> C.sbornik[i];
	}
	return stream;
}

