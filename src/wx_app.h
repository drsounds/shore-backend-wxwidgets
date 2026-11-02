#pragma once

#include <wx/app.h>
#include <shore/app.h>

namespace shore {
namespace backend {
namespace wxwidgets {

class WxApp : public wxApp {
public:
    SHApp* app = nullptr;
    bool OnInit() override { return app->OnInit(); }
};

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
