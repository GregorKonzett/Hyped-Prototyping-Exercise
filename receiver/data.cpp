#include "data.hpp"
#include <iostream>

namespace hyped {

DataStore::DataStore() {

}

void DataStore::writeData(uint8_t key,uint8_t data) {
	store[key] = data;
	std::cout << "Writing Key: " << unsigned(key) << "Data: " << unsigned(data) << std::endl;
}

uint8_t DataStore::readData(uint8_t key) {
	std::cout << "Reading Key: " << unsigned(key) << std::endl;
	return store[key];
}
	
}
