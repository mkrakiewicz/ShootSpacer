/*
 * SmartPointer.cpp
 *
 *  Created on: 19-05-2013
 *      Author: Micha³
 */

#include "SmartPointer.h"

namespace shs {
template<typename T>
inline shs::SmartPointer<T>::SmartPointer(T* pValue) : pData(pValue) {
}

template<typename T>
inline shs::SmartPointer<T>::~SmartPointer() {
	delete pData;
}
}

template<typename T>
inline T& shs::SmartPointer<T>::operator *() {
	return *pData;
}

template<typename T>
inline T* shs::SmartPointer<T>::operator ->() {
	return pData;
}

