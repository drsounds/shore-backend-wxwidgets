#pragma once

#include <wx/dc.h>
#include <wx/gdicmn.h>
#include <wx/wx.h>
#include <shore/canvas.h>

namespace shore {
namespace backend {
namespace wxwidgets {

inline wxColour ToWxColour(SHColor color) {
    return wxColour(color.r, color.g, color.b);
}

class WxCanvas : public SHCanvas {
public:
    WxCanvas(wxDC& dc, wxSize size) : dc_(dc), size_(size) {}
    int Width() const override { return size_.x; }
    int Height() const override { return size_.y; }
    void FillRect(int x, int y, int w, int h, SHColor color) override {
        dc_.SetPen(*wxTRANSPARENT_PEN);
        dc_.SetBrush(wxBrush(ToWxColour(color)));
        dc_.DrawRectangle(x, y, w, h);
    }
    void DrawLine(int x1, int y1, int x2, int y2, SHColor color) override {
        dc_.SetPen(wxPen(ToWxColour(color)));
        dc_.DrawLine(x1, y1, x2, y2);
    }
    void DrawText(int x, int y, const std::string& text, SHColor color) override {
        dc_.SetTextForeground(ToWxColour(color));
        dc_.DrawText(wxString::FromUTF8(text.c_str()), x, y);
    }
private:
    wxDC& dc_;
    wxSize size_;
};

}  // namespace wxwidgets
}  // namespace backend
}  // namespace shore
