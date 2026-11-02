#include "wx_app.h"
#include "wx_backend_impl.h"
#include "wx_peer.h"
#include <shore-backend-wxwidgets/backend.h>

namespace shore {
namespace backend {
namespace wxwidgets {
namespace {
WxApp* g_wxApp = nullptr;
}

std::unique_ptr<SHFramePeer> WxBackend::CreateFramePeer(SHFrame* frame) {
    return std::unique_ptr<SHFramePeer>(new WxPeer(frame));
}
int WxBackend::Run(SHApp* app, int argc, char** argv) {
    g_wxApp = new WxApp;
    g_wxApp->app = app;
    wxApp::SetInstance(g_wxApp);
    if (!wxEntryStart(argc, argv)) return 1;
    int result = 1;
    if (wxTheApp->CallOnInit()) result = wxTheApp->OnRun();
    wxEntryCleanup();
    g_wxApp = nullptr;
    return result;
}
void WxBackend::Quit() { if (wxTheApp) wxTheApp->ExitMainLoop(); }
const char* WxBackend::Name() const { return "wxWidgets"; }

std::unique_ptr<SHBackend> CreateBackend() {
    return std::unique_ptr<SHBackend>(new WxBackend);
}

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
