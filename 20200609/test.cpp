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
			//���ռ�
			T* tmp = new T[n];
			//��������:ǳ����
			//memcpy(tmp, _start, sizeof(T)*size());
			//���: ��ֵ�����
			for (int i = 0; i < size(); ++i) {
				tmp[i] = _start[i];
			}
			//�ͷ�ԭ�пռ�
			delete[] _start;

			//����ָ��
			_start = tmp;
			_finsh = _start + oldsize;
			_eos = _start + n;
		}
	}
	//operator[]�ɶ���д
	T& operator[](size_t pos) {
		if (pos < size())
			return _start[pos];
	}
	//ֻ��
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
	//valĬ��ֵ:�������� 0  �Զ������͵����޲ι���
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			//���
			while (_finsh != _start + n) {
				*_finsh++ = val;
			}
		}
		//����_size
		_finsh = _start + n;
	}
	//�������
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finsh) {
			//���浱ǰλ������ʼλ�õ�ƫ����
			size_t len = size();
			//�������
			if (_finsh == _eos) {
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC); //���ݻᵼ�µ�����ʧЧ,��������,����µ�����
				pos = _start + len;
			}
			//�ƶ�Ԫ��
			iterator end = _finsh;
			while (end > pos) {
				*end = *(end - 1);
				--end;
			}
			//����Ԫ��
			*pos = val;
			//����_size
			++_finsh;
		}
	}
	//ɾ������
	iterator erase(iterator pos) {
		//���ж�ɾ��λ���Ƿ���Ч
		if (pos >= _start && pos < _finsh) {
			//�ƶ�Ԫ��
			iterator begin = pos + 1;
			while (begin < _finsh) {
				*(begin - 1) = *begin;
				++begin;
			}
			//����_size
			--_finsh;
			return pos;//��ʱpos��ɾ��λ�õ���һλ
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
		//����const�ӿ�,ֻ�� �����޸�
		//v[i] = 'a';
	}
	cout << endl;
}


void test() {
	Vector<int> v;


}