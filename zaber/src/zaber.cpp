#include "zaber/zaber.h"

namespace zaber
{
std::shared_ptr<spdlog::logger> Device::m_log          = spdlog::stdout_color_mt("zaber");
size_t                          Device::m_device_count = 0;

} // namespace zaber
