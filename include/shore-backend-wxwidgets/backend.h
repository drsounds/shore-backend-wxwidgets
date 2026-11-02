#pragma once

#include <memory>
#include <shore/backend.h>

namespace shore {
namespace backend {
namespace wxwidgets {

std::unique_ptr<SHBackend> CreateBackend();

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
