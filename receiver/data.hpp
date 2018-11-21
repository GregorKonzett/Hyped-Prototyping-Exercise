#include <map>

namespace hyped {

class DataStore {
  public:
    DataStore();
    void writeData(uint8_t key,uint8_t data);
	uint8_t readData(uint8_t key);

  private:
	std::map<uint8_t,uint8_t> store;

};

} // namespace hyped
