// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp(0);
    tmp.MaxPower = max(MaxPower, s.MaxPower);
    tmp.BitField = BitField|s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp = *this;
    tmp.BitField.SetBit(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp = *this;
    tmp.BitField.ClrBit(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(0);
    tmp.MaxPower = max(MaxPower, s.MaxPower);
    tmp.BitField = BitField&s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp = *this;
    tmp.BitField = ~BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    cin>>s.BitField;
    s.MaxPower = s.BitField.GetLength();
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    cout<<s.BitField;
    return ostr;
}

