#include <iostream>
#include "utils/io/can.hpp"

namespace hyped {
// Forward declarations
namespace utils { class Logger; }
namespace utils { namespace io { class Can; } }
namespace utils { namespace io { class CanProccesor; } }
namespace utils { namespace io { namespace can { struct Frame; } } }

using utils::Logger;
using utils::io::Can;
using utils::io::CanProccesor;

class Sender : public CanProccesor {
  friend Can;

  public:
    Sender();
    bool hasId(uint32_t id, bool extended) override;
    void processNewData(utils::io::can::Frame& message) override;
    void sendData(uint8_t register_, uint8_t data);
    void readData(uint8_t register_);
    void sendSdoMessage();

  private:
    Can&         can_;
    uint8_t node_id_;
    utils::io::can::Frame sdo_message_;
    utils::io::can::Frame nmt_message_;

};

} // namespace hyped
