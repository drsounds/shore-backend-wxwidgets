#pragma once

#include <wx/dcbuffer.h>
#include <wx/wx.h>
#include <map>
#include <shore/frame.h>
#include <shore/view.h>
#include "wx_canvas.h"

namespace shore {
namespace backend {
namespace wxwidgets {

class WxFrame : public wxFrame {
public:
    explicit WxFrame(SHFrame* frame)
        : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8(frame->Title().c_str()),
                  wxDefaultPosition, wxSize(frame->Width(), frame->Height())),
          frame_(frame) {
        CreateStatusBar();
        canvas_ = new wxPanel(this);
        canvas_->SetBackgroundStyle(wxBG_STYLE_PAINT);
        canvas_->Bind(wxEVT_PAINT, [this](wxPaintEvent&) {
            wxAutoBufferedPaintDC dc(canvas_);
            dc.SetBackground(*wxWHITE_BRUSH);
            dc.Clear();
            WxCanvas canvas(dc, canvas_->GetClientSize());
            frame_->Paint(canvas);
        });
        canvas_->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {
            if (frame_->View()) frame_->View()->OnMouseDown(event.GetX(), event.GetY());
        });
        Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
            frame_->Dispatch(event.GetId() - wxID_HIGHEST);
        });
        Bind(wxEVT_TOOL, [this](wxCommandEvent& event) {
            frame_->Dispatch(event.GetId() - wxID_HIGHEST);
        });
    }
    wxMenuBar* Bar() {
        if (!GetMenuBar()) SetMenuBar(new wxMenuBar);
        return GetMenuBar();
    }
    wxPanel* Canvas() const { return canvas_; }
private:
    SHFrame* frame_;
    wxPanel* canvas_ = nullptr;
};

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
