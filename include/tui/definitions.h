#ifndef _TUI_DEFINITIONS_H_
#define _TUI_DEFINITIONS_H_

#define TKEY_ESC                  27
#define TKEY_DOWN               0402
#define TKEY_UP                 0403
#define TKEY_LEFT               0404
#define TKEY_RIGHT              0405
#define TKEY_NPAGE              0522
#define TKEY_PPAGE              0523


typedef enum {
    TALIGN_START,
    TALIGN_CENTER,
    TALIGN_END
} TAlign;

typedef struct TSize {
    int h;
    int w;
} TSize;

#define TSIZE(H, W) (TSize){.h = (H), .w = (W)}

typedef struct TRect {
    TSize;
    int y;
    int x;
} TRect;

#define TRECT(Y, X, H, W) (TRect){.y = (Y), .x = (X), .h = (H), .w = (W)}

#endif /* _TUI_DEFINITIONS_H_ */
