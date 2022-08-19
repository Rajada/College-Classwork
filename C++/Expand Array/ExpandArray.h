/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 6
    May 14, 2014

*****************************************************/

#ifndef EXPAND_ARRAY_H
#define EXPAND_ARRAY_H

const unsigned MIN_ALLOC = 2;

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class IndexOutOfRangeException
{
    private:
        const char* _message;
        const int _i;
        const int _mx;
        const int _mn;

    public:
        IndexOutOfRangeException(const char* m, const int i, const int mx, const int mn = 0)
        :_message(m), _i(i), _mx(mx), _mn(mn){ };
};

template <typename T> class ExpandArray
{
    private:

    T* _array;
    unsigned _alloc;
    unsigned _size;
    int _zero;
    float _percent;

    public:

    ExpandArray(int = 0, float = 0.5);
    ExpandArray(const T*, unsigned s, int i = 0, float p = 0.5);
    ExpandArray(const ExpandArray&);
    ~ExpandArray();
    ExpandArray& operator=(const ExpandArray&);
    template <typename OT> friend ostream& operator<<(ostream&, const ExpandArray<OT>&);
    template <typename OT> friend ostream& operator<<(ostream&, const ExpandArray<OT>*);
    T& operator[](int i);
    const T& operator[](int) const;
    ExpandArray operator()(int first, int last)const;
    void append(const T&);
    void append(const ExpandArray&);
    unsigned size() const;
    void remove(int i);
    void remove(int first, int last);
    void remove();
    void insert(int i, const T&);
    void insert(const T&);
    void write(ofstream&) const;
    void read(ifstream&);
};

unsigned ROUND(float f);

template <typename T> ExpandArray<T>::ExpandArray(int i, float p)
{
    _array = NULL;
    _alloc = 0;
    _size = 0;
    _zero = i;
    _percent = p;
}

template <typename T> ExpandArray<T>::ExpandArray(const T* a, unsigned s, int i, float p)
{
    _array = NULL;
    _alloc = 0;
    _size = 0;
    _zero = i;
    _percent = p;

    for(unsigned j = 0; j < s; j++)
        append(a[j]);
}

template <typename T> ExpandArray<T>::ExpandArray(const ExpandArray<T>& ea)
{
    _array = NULL;
    _alloc = 0;
    _size = 0;
    _zero = ea._zero;
    _percent = ea._percent;

    for(unsigned j = 0; j < ea._size; j++)
        append(ea._array[j]);
}

template <typename T> ExpandArray<T>::~ExpandArray()
{
    if(_array != NULL)
        delete [] _array;
}

template <typename T> ExpandArray<T>& ExpandArray<T>::operator=(const ExpandArray<T>& ea)
{
    if(this == &ea)
        return *this;

    if(_array != NULL)
        delete [] _array;

    _array = NULL;
    _alloc = 0;
    _size = 0;
    _zero = ea._zero;
    _percent = ea._percent;

    for(unsigned j = 0; j < ea._size; j++)
        append(ea._array[j]);

    return *this;
}

template <typename OT> ostream& operator<<(ostream& os, const ExpandArray<OT>& ea)
{
    if(ea._size == 0)
        os << "Array is empty.";
    else
        for(unsigned i = 0; i < ea._size; i++)
            os << ea._array[i] << " ";

    return os;
}

template <typename OT> ostream& operator<<(ostream& os, const ExpandArray<OT>* ea)
{
    return operator<<(os, *ea);
}

template <typename T> T& ExpandArray<T>::operator[](int i)
{
    int temp = i;

    temp -= _zero;

    if((temp < 0) || (temp >= _size))
        throw IndexOutOfRangeException("ExpandArray::operator[](int i)",i,(_size - 1) + _zero, _zero);

    return _array[temp];
}

template <typename T> const T& ExpandArray<T>::operator[](int i) const
{
    int temp = i;

    temp -= _zero;

    if((temp < 0) || (temp >= _size))
        throw IndexOutOfRangeException("ExpandArray::operator[](int i) const",i,(_size - 1) + _zero, _zero);

    return _array[temp];
}

template <typename T> ExpandArray<T> ExpandArray<T>::operator()(int first, int last) const
{
    ExpandArray<T> tempa(_zero, _percent);

    for (int i = first; i < last; i++)
        tempa.append(_array[i - _zero]);

    return tempa;
}

template <typename T> void ExpandArray<T>::append(const T& item)
{
    if(_size == _alloc)
    {
        if(_alloc == 0)
            _alloc = MIN_ALLOC;

        else
        {
            _alloc += ROUND(_alloc * _percent);
        }

        T *temp = new T[_alloc];

        for(unsigned i = 0; i < _size; i++)
        {
            temp[i] = _array[i];
        }

        delete [] _array;
        _array = temp;
    }

    _array[_size] = item;
    _size++;
}

template <typename T> void ExpandArray<T>::append(const ExpandArray& ea)
{
    for(unsigned i = 0; i < ea._size; i++)
    {
        append(ea._array[i]);
    }
}

template <typename T> unsigned ExpandArray<T>::size() const
{
    return _size;
}

template <typename T> void ExpandArray<T>::remove(int i)
{
    int temp = i;

    temp -= _zero;

    if((temp < 0) || (temp >= _size))
        throw IndexOutOfRangeException("ExpandArray::remove(int i)",i,(_size - 1) + _zero, _zero);

    ExpandArray<T> tempa(_zero, _percent);

    for(int j = 0; j < _size; j++)
    {
        if(j != temp)
            tempa.append(_array[j]);
    }

    *this = tempa;
}

template <typename T> void ExpandArray<T>::remove(int first, int last)
{
    int tempf = first;
    int templ = last;
    int temp = 0;

    if(templ < tempf)
    {
        temp = templ;
        templ = tempf;
        tempf = temp;
    }

    for(int j = templ; j >= tempf; j--)
    {
        remove(j);
    }
}

template <typename T> void ExpandArray<T>::remove()
{
    remove(_zero + (_size - 1));
}

template <typename T> void ExpandArray<T>::insert(int i, const T& item)
{
    int temp = i;

    temp -= _zero;

    if((temp < 0) || (temp >= _size))
        throw IndexOutOfRangeException("ExpandArray::insert(int i, const T& item)",i,(_size - 1) + _zero, _zero);

    ExpandArray<T> tempa(*this);

    for(int j = 0; j <= _size; j++)
    {
        if(j < temp)
            tempa._array[j] = _array[j];
        else if(j == temp)
            tempa._array[j] = item;
        else if((j > temp) && (j < _size))
            tempa._array[j] = _array[j - 1];
        else if((j > temp) && (j >= _size))
            tempa.append(_array[j - 1]);
    }

    *this = tempa;
}

template <typename T> void ExpandArray<T>::insert(const T& item)
{
    insert(_zero, item);
}

template <typename T> void ExpandArray<T>::write(ofstream& fout) const
{
    if(!fout)
    {
        cout << "Error: output file not opened." << endl;
    }

    fout.write(reinterpret_cast<const char*>(&_size), sizeof(_size));
    fout.write(reinterpret_cast<const char*>(&_zero), sizeof(_zero));
    fout.write(reinterpret_cast<const char*>(&_percent), sizeof(_percent));
    fout.write(reinterpret_cast<const char*>(_array), sizeof(T) * _size);

    fout.close();
}

template <typename T> void ExpandArray<T>::read(ifstream& fin)
{
    if(!fin)
    {
        cout << "Error: input file not opened." << endl;
    }

    fin.read(reinterpret_cast<char*>(&_size), sizeof(_size));
    fin.read(reinterpret_cast<char*>(&_zero), sizeof(_zero));
    fin.read(reinterpret_cast<char*>(&_percent), sizeof(_percent));

    T* temp = new T[_size];

    fin.read(reinterpret_cast<char*>(temp), sizeof(T) * _percent);

    *this = ExpandArray(temp, _size, _zero, _percent);

    delete [] temp;
}

unsigned ROUND(float f)
{
    unsigned ret = f;

    ret += (f - ret >= 0.5)? 1 : 0;
    ret = (ret < 1)? 1 : ret;

    return ret;
}

#endif
