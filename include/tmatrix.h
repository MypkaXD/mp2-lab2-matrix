// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
      if (sz <= 0)
        throw out_of_range("ERROR: Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("ERROR: Vector size should be less than MAX_VECTOR_SIZE = 100000000");
      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz <= 0)
            throw out_of_range("ERROR: Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("ERROR: Vector size should be less than MAX_VECTOR_SIZE = 100000000");

        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        sz = 0;
        delete[] pMem;
        pMem = nullptr;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        //if (&v == this)//провекрка на самоприсваивание
        //    return *this;
        //if (sz != v.sz) {
        //    TDynamicVector tmp(v);
        //    swap(*this, tmp);
        //}
        //swap(*this, v);


        if (&v == this)//провекрка на самоприсваивание
            return *this;

        if (sz != v.sz) {//если sz == v.sz перевыделять память не нужно
            T* tmp = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = tmp;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }
    
    size_t size() const noexcept { 
        return sz; 
    }
    
    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0) {
            throw "ERROR: Negative index";
        }
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0) {
            throw "ERROR: Negative index";
        }
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0) {
            throw "ERROR: Negative index";
        }
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0) {
            throw "ERROR: Negative index";
        }
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";
        return pMem[ind];
    }
    
    //сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
         if (sz != v.sz)
             return false;
         for (size_t count = 0; count < sz; count++) {
             if (pMem[count] != v.pMem[count])
                 return false;
         }
         return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return (!(*this == v));
    }
    
    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] + val;
        return tmp;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector tmp(sz);
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] - val;
        return tmp;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector tmp(sz);
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] *= val;
        return tmp;
    }
    
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (this->sz != v.sz)
            throw "ERROR: NOT EQUAL SIZE OF VECRTORS";
        TDynamicVector tmp(sz);
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] + v.pMem[count];
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (this->sz != v.sz)
            throw "ERROR: NOT EQUAL SIZE OF VECRTORS";
        TDynamicVector tmp(this->sz);
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] - v.pMem[count];
        return tmp;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (this->sz != v.sz)
            throw "ERROR: NOT EQUAL SIZE OF VECRTORS";
        T result{ 0 };
        for (size_t count = 0; count < sz; count++)
            result += pMem[count] * v.pMem[count];
        return result;
    }
    
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
    }
    
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
      for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
      for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
      return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }
  
  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }
  
  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }
  
  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }
  
  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
