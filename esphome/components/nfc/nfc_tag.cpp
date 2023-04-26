#include "nfc.h"
#include "nfc_tag.h"

namespace esphome {
namespace nfc {

static const char *const TAG = "nfc.tag";

std::string NfcTag::get_ha_tag_id() {
  if (!this->has_ndef_message()) {
    return std::string();
  }
  auto message = this->get_ndef_message();
  auto records = message->get_records();
  for (auto record : records) {
    std::string payload = record->get_payload();
    size_t pos = payload.find(HA_TAG_ID_PREFIX);
    if (pos != std::string::npos) {
      return payload.substr(pos + sizeof(HA_TAG_ID_PREFIX) - 1);
    }
  }
  return std::string();
}

}  // namespace nfc
}  // namespace esphome
