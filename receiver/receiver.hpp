#include "utils/io/can.hpp"
#include "data.hpp"

namespace hyped {
// Forward declarations
namespace utils { class Logger; }
namespace utils { namespace io { class Can; } }
namespace utils { namespace io { class CanProccesor; } }
namespace utils { namespace io { namespace can { struct Frame; } } }

using utils::Logger;
using utils::io::Can;
using utils::io::CanProccesor;

class Receiver : public CanProccesor {
  friend Can;

  public:
    Receiver();
    bool hasId(uint32_t id, bool extended) override;
    void writeDataIntoStore(uint8_t key,uint8_t data);
    void readDataFromStore(uint8_t key);
    void processNewData(utils::io::can::Frame& message) override;
    void sendSdoMessage();

  private:
    DataStore   data_store_;
    Can&         can_;
    uint8_t node_id_;
    utils::io::can::Frame sdo_message_;
    utils::io::can::Frame nmt_message_;

};

} // namespace hyped
