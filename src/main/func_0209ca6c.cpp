/* func_0209ca6c @ 0x0209ca6c, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Dir {
    s16 x;
    s16 y;
    Dir(s16 a, s16 b) : x(a), y(b) {}
};
extern "C" int func_0209cc30(void *ctx, int x, int y);
extern "C" int func_0209d030(int *);
extern "C" int func_0209d01c(int t, int arg);
extern "C" int func_020644cc(int n);
extern "C" int func_0209ca6c(void *ctx, int want, int arg)
{
    int found;
    unsigned int x;
    unsigned int y;
    unsigned int i;
    int count;
    int k;
    int j;
    Dir *d;
    found = 0;
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            if (want == func_0209d030((int *) func_0209cc30(ctx, x, y))) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            break;
        }
    }
    if (found != 0) {
        static Dir dirs[4] = {Dir(-1, 0), Dir(1, 0), Dir(0, 1), Dir(0, -1)};
        count = 0;
        for (i = 0; i < 4; i++) {
            d = &dirs[i];
            if (func_0209d030((int *) func_0209cc30(ctx, x + d->x, y + d->y)) == 9) {
                count++;
            }
        }
        if (count != 0) {
            k = func_020644cc(count);
            j = 0;
            for (i = 0; i < 4; i++) {
                d = &dirs[i];
                if (func_0209d030((int *) func_0209cc30(ctx, x + d->x, y + d->y)) == 9) {
                    if (k == j) {
                        func_0209d01c(func_0209cc30(ctx, x + d->x, y + d->y), arg);
                        return 1;
                    }
                    j++;
                }
            }
        }
    }
    return 0;
}
