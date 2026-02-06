#ifndef _TUI_STATUS_BAR_H_
#define _TUI_STATUS_BAR_H_

#include <tui/widget.h>


typedef struct {
    TWidget;
} TStatusBar;


extern const twidget_class *TStatusBarCls;


TStatusBar *tstatusbar_new(void);
void tstatusbar_init(TStatusBar *self);
void tstatusbar_vinit(TStatusBar *self, va_list va);

void tstatusbar_destroy(TStatusBar *self);
void tstatusbar_delete(TStatusBar *self);

#endif /* _TUI_STATUS_BAR_H_ */
