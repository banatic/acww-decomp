/* func_ov003_02227cec @ 0x02227cec, 0x1a8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x28];
} Cell;
typedef struct {
    Cell *cells;
    int w;
    int h;
} UnkStruct_02227cec;
typedef struct {
    u8 x, y;
} UnkStruct_02227cec_2;

extern UnkStruct_02227cec *data_021c80bc;
extern int func_02037d9c(Cell *c);
extern int func_02037e70(Cell *c);

int func_ov003_02227cec(int unused, UnkStruct_02227cec_2 *out, int *n, unsigned kind)
{
    int ret;
    UnkStruct_02227cec *g;
    int x, y;
    Cell *c;
    int f;

    ret = 0;
    g = data_021c80bc;
    if (g != 0) {
        for (x = 1; x < g->h - 1; x++) {
            for (y = 1; y < g->w - 1; y++) {
                c = ((unsigned) x < (unsigned) g->w && (unsigned) y < (unsigned) g->h && g->cells != 0)
                        ? &g->cells[y * g->w + x]
                        : 0;
                if (c == 0) {
                    continue;
                }
                switch (kind) {
                    case 6:
                        if (func_02037d9c(c) & 8) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 0:
                        if (func_02037d9c(c) & 0x7f000) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 1:
                        if (func_02037d9c(c) & 0x100) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 2:
                        if (func_02037d9c(c) & 0x80000) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 3:
                        if (func_02037e70(c) != 0) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 4:
                        f = func_02037d9c(c);
                        if (f & 0x7f000) {
                            if (f & 8) {
                                out[*n].x = x;
                                out[*n].y = y;
                                *n = *n + 1;
                            }
                        }
                        break;
                    case 5:
                        if (func_02037d9c(c) & 8) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                }
            }
        }
    }
    if (*n > 0) {
        ret = 1;
    }
    return ret;
}
