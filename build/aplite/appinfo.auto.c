#include "pebble_process_info.h"
#include "src/resource_ids.auto.h"

const PebbleProcessInfo __pbl_app_info __attribute__ ((section (".pbl_header"))) = {
  .header = "PBLAPP",
  .struct_version = { PROCESS_INFO_CURRENT_STRUCT_VERSION_MAJOR, PROCESS_INFO_CURRENT_STRUCT_VERSION_MINOR },
  .sdk_version = { PROCESS_INFO_CURRENT_SDK_VERSION_MAJOR, PROCESS_INFO_CURRENT_SDK_VERSION_MINOR },
  .process_version = { 1, 1 },
  .load_size = 0xb6b6,
  .offset = 0xb6b6b6b6,
  .crc = 0xb6b6b6b6,
  .name = "spike_pebble_watchface",
  .company = "jrohall",
  .icon_resource_id = DEFAULT_MENU_ICON,
  .sym_table_addr = 0xA7A7A7A7,
  .flags = PROCESS_INFO_WATCH_FACE | PROCESS_INFO_PLATFORM_APLITE,
  .num_reloc_entries = 0xdeadcafe,
  .uuid = { 0x06, 0x8F, 0x02, 0xD1, 0x92, 0x20, 0x4C, 0x3F, 0xAC, 0xD5, 0xDA, 0x19, 0x57, 0x9D, 0xA4, 0xC3 },
  .virtual_size = 0xb6b6
};
