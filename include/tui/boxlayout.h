#ifndef _TUI_BOX_LAYOUT_H_
#define _TUI_BOX_LAYOUT_H_

#include <masc/list.h>
#include <tui/widget.h>


typedef enum {
    TBOX_LAYOUT_DIR_VERTIAL,
    TBOX_LAYOUT_DIR_HORIZONTAL
} TBoxLayoutDirection;

typedef struct {
    TWidget;
    TBoxLayoutDirection dir;
    List children;
} TBoxLayout;


extern const twidget_class *TBoxLayoutCls;


TBoxLayout *tboxlayout_new(TBoxLayoutDirection dir);
void tboxlayout_init(TBoxLayout *self, TBoxLayoutDirection dir);
void tboxlayout_vinit(TBoxLayout *self, va_list va);

void tboxlayout_destroy(TBoxLayout *self);
void tboxlayout_delete(TBoxLayout *self);

#endif /* _TUI_BOX_LAYOUT_H_ */
