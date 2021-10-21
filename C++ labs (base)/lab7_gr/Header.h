#pragma once
#include <iostream>
template <class T>
class Store
{
private:
	T data[100];
	int n;
public:
	
	Store(){
		n = 0;
	}
	void add(T x){
		data[n] = x;
		n++;
	}
	void del() {
		n--;
	}
	class iterator{
	private:
		int index;
		Store* pdata;
	public:
		iterator(){
			index = 0;
			pdata = NULL;
		}
		iterator(int i, Store* p){
			index = i;
			pdata = p;
		}
		void operator++(int) {
			index += 2;
			if (index == pdata->n + 1) index = pdata->n;
		}
		int operator !=(iterator x){
			if (index != x.index)
				return 1;
			else
				return 0;
		}
		int operator ==(iterator x){
			if (index == x.index)
				return 1;
			else
				return 0;
		}
		T& operator*(){
			if (pdata){
				return pdata->data[index];
			}
			else{
			throw 0;
			}
		}
	};
	iterator begin(){
		return iterator(0, this);
	}
	iterator end(){
		 return iterator(n, this); 

	}

};