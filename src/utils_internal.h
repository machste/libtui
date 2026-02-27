#ifndef _TUI_UTILS_INTERNAL_H_
#define _TUI_UTILS_INTERNAL_H_

#ifndef _NCURSES
#define filter ncurses_filter
    #include <ncurses.h>
#undef filter
#endif

#include <tui/utils.h>


const cchar_t *tlinestyle_char(TLineStyle style, TAxis dir);

#endif /* _TUI_UTILS_INTERNAL_H_ */
