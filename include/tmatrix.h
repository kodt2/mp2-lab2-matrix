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
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz > MAX_VECTOR_SIZE) {
            throw "Vector size should be smaler than 100000000";
        }
        if (sz == 0) {
            throw out_of_range("Vector size should be greater than zero");
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
        
    }
      /*TDynamicVector() {
          sz = 1;
          pMem = new T[sz]();
          pMem[0] = 0;
      }
      TDynamicVector(size_t s)
      {
          if (s <= 0){
              throw "Vector size should be greater than 0";
          }
          if (s > MAX_VECTOR_SIZE) {
              throw "Vector size should be smaler than 100000000";
          }
          sz = s;
          pMem = new T[sz];// {}; // У типа T д.б. констуктор по умолчанию
          for (int i = 0; i < sz; i++) {
              pMem[i] = 0;
          }
      }*/
      TDynamicVector(T* arr, size_t s) : sz(s)
      {
          if (sz == 0) {
              throw out_of_range("Vector size should be greater than 0");
          }
          if (sz > MAX_VECTOR_SIZE) {
              throw "Vector size should be smaler than 100000000";
          }
          assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
          pMem = new T[sz];
          std::copy(arr, arr + sz, pMem);
      }
      TDynamicVector(const TDynamicVector& v)
      {
          sz = v.sz;
          pMem = new T[sz];
          for (int i=0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      TDynamicVector(TDynamicVector&& v) noexcept
      {
          sz = v.sz;
          pMem = v.pMem;
          v.pMem = nullptr;
      }
      ~TDynamicVector()
      {
          delete[] pMem;
      }
      TDynamicVector& operator=(const TDynamicVector& v)
      {
          sz = v.sz;
          pMem = new T[sz];
          for (int i=0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
          return *this;
      }
      TDynamicVector& operator=(TDynamicVector&& v) noexcept
      {
          sz = v.sz;
          pMem = v.pMem;
          v.pMem = nullptr;
          return *this;
      }

      size_t size() const noexcept { return sz; }

      // индексация
      T& operator[](size_t ind)
      { 
          if (ind < 0 || ind >= sz) {
              throw "ind < 0 || ind >= size";
          }
          return pMem[ind];
      }
      const T& operator[](size_t ind) const
      {
          if (ind < 0 || ind >= sz) {
              throw "ind < 0 || ind >= size";
          }
          return pMem[ind];
      }
      // индексация с контролем
      T& at(long long int ind)
      {
          if (ind < 0 || ind >= sz) {
              throw "violation of the boundaries of the array";
          }
          return pMem[ind];
      }
      const T& at(long long int ind) const
      {
          if (ind < 0 || ind >= sz) {
              throw "violation of the boundaries of the array";
          }
              return pMem[ind];
      }

      // сравнение
      bool operator==(const TDynamicVector& v) const noexcept
      {
          bool similar = true;
          if (sz != v.sz) {
              return false;
          }
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  similar = false;
                  i = sz;
              }
          }
          return similar;
      }
      bool operator!=(const TDynamicVector& v) const noexcept
      {
          bool similar = false;
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  similar = true;
                  i = sz;
              }
          }
          return similar;
      }

      // скалярные операции
      TDynamicVector operator+(T val)
      {
          TDynamicVector res = TDynamicVector(sz);
          for (int i = 0; i < sz; i++) {
              res.pMem[i] = pMem[i] + val;
          }
          return res;
      }
      TDynamicVector operator-(double val)
      {
          TDynamicVector res = TDynamicVector(sz);
          for (int i = 0; i < sz; i++) {
              res.pMem[i] = pMem[i] - val;
          }
          return res;
      }
      TDynamicVector operator*(double val)
      {
          TDynamicVector res = TDynamicVector(sz);
          for (int i = 0; i < sz; i++) {
              res.pMem[i] = pMem[i] * val;
          }
          return res;
      }

      // векторные операции
      TDynamicVector operator+(const TDynamicVector& v)
      {
          TDynamicVector res = TDynamicVector(std::max(sz, v.sz));
          for (int i = 0; i < min(sz, v.sz); i++) {
              res[i] = pMem[i] + v.pMem[i];
          }
          if (sz > v.sz) {
              for (int i = v.sz; i < sz; i++) {
                  res[i] = pMem[i];
              }
          }
          else {
              for (int i = sz; i < v.sz; i++) {
                  res[i] = v.pMem[i];
              }
          }
          return res;
      }
      TDynamicVector operator-(const TDynamicVector& v)
      {
          TDynamicVector res = TDynamicVector(std::max(sz, v.sz));
          for (int i = 0; i < min(sz, v.sz); i++) {
              res[i] = pMem[i] - v.pMem[i];
          }
          if (sz > v.sz) {
              for (int i = v.sz; i < sz; i++) {
                  res[i] = pMem[i];
              }
          }
          else {
              for (int i = sz; i < v.sz; i++) {
                  res[i] = -v.pMem[i];
              }
          }
          return res;
      }
      T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
      {
          T res = 0;
          for (int i = 0; i < min(sz, v.sz); i++) {
              res += pMem[i] * v.pMem[i];
          }
          return res;
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
            if (sz > MAX_MATRIX_SIZE) {
                throw "Matrix size should be smaler than 10000";
            }
            for (size_t i = 0; i < sz; i++)
                pMem[i] = TDynamicVector<T>(sz);
        }

      using TDynamicVector<TDynamicVector<T>>::operator[];

      // сравнение
      bool operator==(const TDynamicMatrix& v) const noexcept
      {
          bool similar = true;
          if (sz != v.sz) {
              return false;
          }
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  similar = false;
                  i = sz;
              }
          }
          return similar;
      }

      // матрично-скалярные операции
      TDynamicMatrix<T> operator*(const T& val)
      {
          TDynamicMatrix<T> res(sz);
          for (int i = 0; i < sz; i++) {
              for (int j = 0; j < sz; j++) {
                  res[i][j] = pMem[i][j] * val;
              }
          }
          return res;

      }

      // матрично-векторные операции
      TDynamicVector<T> operator*(const TDynamicVector<T>& v)
      {
          if (v.size() != sz) {
              throw "wrong size of vector"
          }
          TDynamicVector<T> res(sz);
          for (int i = 0; i < sz; i++) {
              
              res[i] = v * pMem[i];
          }
          return res;
      }

      // матрично-матричные операции
      TDynamicMatrix operator+(const TDynamicMatrix& m)
      {
          TDynamicMatrix<T> res(std::max(sz, m.sz));
          for (int i = 0; i <std::min( sz, m.sz); i++) {
              for (int j = 0; j < std::min(sz, m.sz); j++) {
                  res[i][j] = pMem[i][j] + m[i][j];
              }
          }
          if (sz > m.sz) {
              for (int i = m.sz; i < sz; i++) {
                  for (int j = m.sz; j < sz; j++) {
                      res[i][j] = pMem[i][j];
                  }
              }
          }
          else {
              for (int i = sz; i < m.sz; i++) {
                  for (int j = sz; j < m.sz; j++) {
                      res[i][j] = m[i][j];
                  }
              }
          }
          return res;
      }
      TDynamicMatrix operator-(const TDynamicMatrix& m)
      {
          TDynamicMatrix<T> res(std::max(sz, m.sz));
          for (int i = 0; i < std::min(sz, m.sz); i++) {
              for (int j = 0; j < std::min(sz, m.sz); j++) {
                  res[i][j] = pMem[i][j] - m[i][j];
              }
          }
          if (sz > m.sz) {
              for (int i = m.sz; i < sz; i++) {
                  for (int j = m.sz; j < sz; j++) {
                      res[i][j] = pMem[i][j];
                  }
              }
          }
          else {
              for (int i = sz; i < m.sz; i++) {
                  for (int j = sz; j < m.sz; j++) {
                      res[i][j] = m[i][j];
                  }
              }
          }
          return res;
      }
      TDynamicMatrix operator*(const TDynamicMatrix& m)
      {
          TDynamicMatrix<T> res(sz);
          TDynamicMatrix<T> m1;
          m1 = m.transposing();
          for (int i = 0; i < sz; i++) {
              for (int j = 0; j < sz; j++) {
                  res[i][j] = pMem[i] * m1[j];
              }
          }
          return res;
      }
      TDynamicMatrix transposing() {
          TDynamicMatrix<T> res(sz);
          for (int i = 0; i < sz; i++) {
              for (int j = 0; j < sz; j++) {
                  res[i][j] = pMem[j][i];
              }
          }
          return res;
      }
      size_t size() const noexcept {
          return sz;
      }
      // ввод/вывод
      friend istream& operator>>(istream& istr, TDynamicMatrix& v)
      {
          for (size_t i = 0; i < v.sz; i++)
              istr >> v.pMem[i]; // требуется оператор>> для типа T
          return istr;
      }
      friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
      {
          for (size_t i = 0; i < v.sz; i++)
              ostr << v.pMem[i] << '\n'; // требуется оператор<< для типа T
          return ostr;
      }
    };

    #endif
