#pragma once

#include <map>
#include <shore/backend.h>
#include <shore/frame.h>
#include <shore/toolbar.h>
#include "wx_frame.h"

namespace shore {
namespace backend {
namespace wxwidgets {

class WxPeer : public SHFramePeer {
public:
    explicit WxPeer(SHFrame* frame) : window_(new WxFrame(frame)) {}
    ~WxPeer() override { if (window_) window_->Destroy(); }
    void SetTitle(const std::string& title) override {
        window_->SetTitle(wxString::FromUTF8(title.c_str()));
    }
    void SetStatusText(const std::string& text) override {
        window_->SetStatusText(wxString::FromUTF8(text.c_str()));
    }
    void AddMenuItem(const std::string& menu, const std::string& label, int id) override {
        wxString menuTitle = wxString::FromUTF8(menu.c_str());
        wxMenu*& menuPointer = menus_[menu];
        if (!menuPointer) {
            menuPointer = new wxMenu;
            window_->Bar()->Append(menuPointer, menuTitle);
        }
        menuPointer->Append(wxID_HIGHEST + id, wxString::FromUTF8(label.c_str()));
    }
    void SetToolBar(const SHToolBar& toolbar) override {
        wxToolBar* bar = window_->GetToolBar()
            ? window_->GetToolBar()
            : window_->CreateToolBar(wxTB_TEXT | wxTB_NOICONS);
        bar->ClearTools();
        for (const auto& item : toolbar.Items()) {
            if (item.separator) bar->AddSeparator();
            else bar->AddTool(wxID_HIGHEST + item.id,
                              wxString::FromUTF8(item.label.c_str()), wxNullBitmap);
        }
        bar->Realize();
    }
    void Show(bool show) override { window_->Show(show); }
    void Invalidate() override { window_->Canvas()->Refresh(); }
private:
    WxFrame* window_;
    std::map<std::string, wxMenu*> menus_;
};

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
