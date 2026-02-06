#ifndef _TUI_MAIN_LAYOUT_H_
#define _TUI_MAIN_LAYOUT_H_

#include <tui/widget.h>
#include <tui/titlebar.h>
#include <tui/statusbar.h>


typedef struct {
    TWidget;
    TTitleBar title_bar;
    TWidget *center_widget;
    TStatusBar status_bar;
} TMainLayout;


extern const twidget_class *TMainLayoutCls;


TMainLayout *tmainlayout_new(const char *title);
void tmainlayout_init(TMainLayout *self, const char *title);
void tmainlayout_vinit(TMainLayout *self, va_list va);

void tmainlayout_destroy(TMainLayout *self);
void tmainlayout_delete(TMainLayout *self);

void tmainlayout_set_center(TMainLayout *self, TWidget *widget);

#endif /* _TUI_MAIN_LAYOUT_H_ */
