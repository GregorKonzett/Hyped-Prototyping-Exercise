#include "receiver.hpp"
#include "utils/io/can.hpp"
#include <iostream>
namespace hyped {

using utils::io::can::Frame;

constexpr uint32_t kEmgyTransmit          = 0x80;
constexpr uint32_t kSdoReceive            = 0x600;
constexpr uint32_t kSdoTransmit           = 0x580;
constexpr uint32_t kNmtReceive            = 0x000;
constexpr uint32_t kNmtTransmit           = 0x700;

// Function codes for sending messages
constexpr uint8_t  kReadObject            = 0x40;
constexpr uint8_t  kWriteOneByte          = 0x2F;
constexpr uint8_t  kWriteTwoBytes         = 0x2B;
// constexpr uint8_t  kWriteThreeBytes       = 0x27;  // TODO(anyone) add back in if needed
constexpr uint8_t  kWriteFourBytes        = 0x23;

// Network management commands
constexpr uint8_t  kNmtOperational        = 0x01;

constexpr uint8_t reading = 0x40;
constexpr uint8_t writing = 0x23;

Receiver::Receiver()
  : can_(Can::getInstance()),
  node_id_(0x001),
  data_store_(DataStore())
{
	std::cout << "Initializing receiver" << std::endl;
	    	sdo_message_.id       = kSdoReceive + node_id_;
    sdo_message_.extended = false;
    sdo_message_.len      = 8;
    nmt_message_.id       = kNmtReceive;
    nmt_message_.extended = false;
    nmt_message_.len      = 2;
    can_.start();
    can_.registerProcessor(this);
}

bool Receiver::hasId(uint32_t id, bool extended) {
    std::cout << "hasID called: " << id << std::endl;
    return true;
}

void Receiver::processNewData(utils::io::can::Frame& message) {
std::cout << "Data arrived" << std::endl;
    uint32_t id = message.data[0];
    if (id == reading) {
        readDataFromStore(message.data[1]);
    } else if (id == writing) {
        writeDataIntoStore(message.data[1],message.data[2]);
    }
}

void Receiver::sendSdoMessage()
{
    can_.send(sdo_message_);
}

void Receiver::writeDataIntoStore(uint8_t key,uint8_t data) {
    data_store_.writeData(key,data);
}

void Receiver::readDataFromStore(uint8_t key) {
    uint8_t data = data_store_.readData(key);

    //sdo_message_.id = 0x001;
    sdo_message_.data[0] = reading;
    sdo_message_.data[1] = data;

    for(int i = 2;i<sizeof(sdo_message_.data[0]);i++) {
        sdo_message_.data[i] = 0x00;
    }

    sendSdoMessage();
    
}
    

} // namespace hyped
