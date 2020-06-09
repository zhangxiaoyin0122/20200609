#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <class T>
class Vector {
public:
	Vector()
		:_start(nullptr)
		,_finsh(nullptr)
		,_eos(nullptr)
	{}

	size_t size()const {
		return _finsh - _start;
	}
	size_t capacity()const {
		return _eos - _start;
	}

	void pushBack(const T& val) {
		if (_finsh == _eos) {
			size_t newC = capacity()==0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		*_finsh = val;
		++_finsh;
	}
	void reserve(size_t n) {
		if (n > capacity()) {
			size_t oldsize = size();
			//开空间
			T* tmp = new T[n];
			//拷贝内容:浅拷贝
			//memcpy(tmp, _start, sizeof(T)*size());
			//深拷贝: 赋值运算符
			for (int i = 0; i < size(); ++i) {
				tmp[i] = _start[i];
			}
			//释放原有空间
			delete[] _start;

			//更新指针
			_start = tmp;
			_finsh = _start + oldsize;
			_eos = _start + n;
		}
	}
	//operator[]可读可写
	T& operator[](size_t pos) {
		if (pos < size())
			return _start[pos];
	}
	//只读
	const T& operator[](size_t pos)const {
		if (pos < size())
			return _start[pos];
	}
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finsh;
	}
	const_iterator begin() const{
		return _start;
	}
	const_iterator end() const{
		return _finsh;
	}
	//val默认值:内置类型 0  自定义类型调用无参构造
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			//填充
			while (_finsh != _start + n) {
				*_finsh++ = val;
			}
		}
		//更新_size
		_finsh = _start + n;
	}
	//插入操作
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finsh) {
			//保存当前位置与起始位置的偏移量
			size_t len = size();
			//检查容量
			if (_finsh == _eos) {
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC); //增容会导致迭代器失效,如有增容,须更新迭代器
				pos = _start + len;
			}
			//移动元素
			iterator end = _finsh;
			while (end > pos) {
				*end = *(end - 1);
				--end;
			}
			//插入元素
			*pos = val;
			//更新_size
			++_finsh;
		}
	}
	//删除操作
	iterator erase(iterator pos) {
		//先判断删除位置是否有效
		if (pos >= _start && pos < _finsh) {
			//移动元素
			iterator begin = pos + 1;
			while (begin < _finsh) {
				*(begin - 1) = *begin;
				++begin;
			}
			//更新_size
			--_finsh;
			return pos;//此时pos是删除位置的下一位
		}
	}
private:
	T* _start;
	T* _finsh;
	T* _eos; // end_of_stone

};

template <class T>
void VectorPrint(const Vector<T>& v) {
	for (int i = 0; i < size(); ++i) {
		cout << v[i] << " ";
		//调用const接口,只读 不能修改
		//v[i] = 'a';
	}
	cout << endl;
}


void test() {
	Vector<int> v;


}