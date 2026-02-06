#ifndef _TUI_TITLE_BAR_H_
#define _TUI_TITLE_BAR_H_

#include <tui/widget.h>


typedef struct {
    TWidget;
    char *title;
} TTitleBar;


extern const twidget_class *TTitleBarCls;


TTitleBar *ttitlebar_new(const char *title);
void ttitlebar_init(TTitleBar *self, const char *title);
void ttitlebar_vinit(TTitleBar *self, va_list va);

void ttitlebar_destroy(TTitleBar *self);
void ttitlebar_delete(TTitleBar *self);

#endif /* _TUI_TITLE_BAR_H_ */
