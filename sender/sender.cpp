#include "sender.hpp"
#include "utils/io/can.hpp"

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

Sender::Sender()
  : can_(Can::getInstance()),
  node_id_(0x001)
{
    sdo_message_.id       = kSdoReceive + node_id_;
    sdo_message_.extended = false;
    sdo_message_.len      = 8;
    nmt_message_.id       = kNmtReceive;
    nmt_message_.extended = false;
    nmt_message_.len      = 2;
    can_.start();
    can_.registerProcessor(this);
}

bool Sender::hasId(uint32_t id, bool extended) {
    return true;
}

void Sender::processNewData(utils::io::can::Frame& message) {
    uint32_t id = message.data[0];
    if (id == reading) {
        std::cout << "Data received: "<< unsigned(message.data[1]) << std::endl;
    }
}

void Sender::sendData(uint8_t register_, uint8_t data)
{
    //sdo_message_.id = writing;
    sdo_message_.data[0] = writing;
    sdo_message_.data[1] = register_;
    sdo_message_.data[2] = data;
    
    for(int i = 3;i<sizeof(sdo_message_.data[0]);i++) {
        sdo_message_.data[i] = 0x00;
    }

    sendSdoMessage();
}

void Sender::readData(uint8_t register_) {
	std::cout << "Read Data called" << std::endl;
    //sdo_message_.id = reading;
    sdo_message_.data[0] = reading;
    sdo_message_.data[1] = register_;

    for(int i = 2;i<sizeof(sdo_message_.data[0]);i++) {
        sdo_message_.data[i] = 0x00;
    }

    sendSdoMessage();
}

void Sender::sendSdoMessage()
{
    std::cout << "Sending message";	
    can_.send(sdo_message_);
}

} // namespace hyped
