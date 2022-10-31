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
        if (ind < 0)
            throw "ERROR: Negative index";
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";

        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0)
            throw "ERROR: Negative index";
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";

        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0)
            throw "ERROR: Negative index";
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";

        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0)
            throw "ERROR: Negative index";
        if (ind > sz)
            throw "ERROR: TOO LARGE INDEX";

        return pMem[ind];
    }
    
    //сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        //if (*this == &v)
        //    return true;
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
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(sz);

        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] - val;

        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(sz);

        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] * val;

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
        if (s <= 0)
            throw "ERROR: MATRIX SIZE SHOULD BE GREATER THAN ZERO";
        if (s > MAX_MATRIX_SIZE)
            throw "ERROR: TO MUCH SIZE OF MATRIX. MAX SIZE IS 10000";
    
        for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
    }
    
    using TDynamicVector<TDynamicVector<T>>::operator[];
    
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m); //такую штуку разбирали на паре по АиСДу
        //if (sz != m.sz)
        //    return false;
        //for (int count = 0; count < sz; count++) {
        //    if (pMem[count] != m.pMem[count])
        //        return false;
        //}
        //return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(m == *this);
    }
    
    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
    
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] * val;
        return tmp;
    }
    
    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicMatrix tmp(sz);
    
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] * v;
    
        return tmp;
    }
    
    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "ERROR: Addition of different sizes of matrices is not allowed";
    
        TDynamicMatrix tmp(sz);
    
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] + m.pMem[count];
    
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "ERROR: Subtraction of different matrix sizes is not allowed";
    
        TDynamicMatrix tmp(sz);
    
        for (size_t count = 0; count < sz; count++)
            tmp.pMem[count] = pMem[count] - m.pMem[count];
    
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "ERROR: Multiplication of different sizes of matrices is not allowed";
    
        TDynamicMatrix tmp(sz);
    
        for (size_t i = 0; i < sz; i++)
            for (size_t k = 0; k < sz; k++)
                for (size_t j = 0; j < sz; j++)
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
    
        return tmp;
    }
    size_t size() const noexcept {
        return TDynamicVector<TDynamicVector<T>>::size();//не уверен, что работает, но такой код отобразил 10
        /*
            TDynamicMatrix<int> m1(10);
         std::cout << m1.size() << std::endl;
        */
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m){
        for (size_t count = 0; count < m.sz; count++)
            istr >> m.pMem[count] << "\t";
    
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
        for (int count = 0; count < m.sz; count++)
            ostr << m.pMem[count] << "\t";
    
        return ostr;
    }
};

#endif
