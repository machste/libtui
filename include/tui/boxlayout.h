#ifndef _TUI_BOX_LAYOUT_H_
#define _TUI_BOX_LAYOUT_H_

#include <masc/list.h>
#include <tui/widget.h>


typedef struct {
    TWidget;
    TAxis dir;
    List children;
} TBoxLayout;


extern const twidget_class *TBoxLayoutCls;


TBoxLayout *tboxlayout_new(TAxis dir);
void tboxlayout_init(TBoxLayout *self, TAxis dir);
void tboxlayout_vinit(TBoxLayout *self, va_list va);

void tboxlayout_destroy(TBoxLayout *self);
void tboxlayout_delete(TBoxLayout *self);

void tboxlayout_add(TBoxLayout *self, TWidget *widget);

void tboxlayout_draw(TBoxLayout *self);
void tboxlayout_geometry(TBoxLayout *self, TRect r);

#endif /* _TUI_BOX_LAYOUT_H_ */
