#pragma once
#include"../Log.h"


// TODO. need to check the data size that puched

namespace imatics {
	template<typename T>
	class mesh {
	public:
		T* m_staticmesh = nullptr;
		T* m_daynamicmesh = nullptr;
		size_t m_count = 0; // how many data int the array like index
	private:
		size_t m_capacity = 0; // how much can it hold
		size_t m_expblock = 2; // expected block 
	private:
		//alloc new memory 
		void memalloc(size_t new_count) {
			size_t nblock = m_count + new_count;
			m_capacity = nblock + m_expblock;			
			T* tmesh = new T[m_capacity]; 
			for (int i = 0; i < m_count; i++) 
				tmesh[i] = std::move(m_staticmesh[i]);

			delete[] m_staticmesh;
			m_staticmesh = tmesh;
		}
	public:
		mesh(T* data, size_t alloc){
			m_staticmesh = new T[alloc];
			push(data, alloc);
		}
		//push a block of memory
		void push(T* data, size_t new_count) {
			if(m_capacity <= m_count + new_count)
				memalloc(new_count);
			for (int i = 0; i < new_count; i++) {
				m_staticmesh[m_count + i] = data[i];
			}
			m_count = new_count;


		}
		~mesh() {
			delete[] m_staticmesh;
		}
		//to delete a block of memory
		void pull(size_t index) {
			if (index < m_count) {
				for (; index < m_count - 1; index++) {
					m_staticmesh[index] = m_staticmesh[index + 1];
				}
				m_count--;
				m_capacity++;
			}

		}
	};
}