/* func_0203c23c @ 0x0203c23c, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad[0x178];
    int a;
    int b;
    int c;
    int d;
} Input;

typedef struct {
    int v;
    int pad;
    int w;
} Output;

int func_0203c23c(Input *in, Output *out)
{
    int changed = 0;
    int a, b, c, d;
    int diff, diff_y;
    int max, cur, min;
    int max_y, cur_y, min_y;

    a = in->a;
    b = in->b;
    diff = b - a;
    if (diff <= 0xa000) {
        out->v = (b + a) >> 1;
        changed = 1;
    } else {
        max = a + 0x5000;
        cur = out->v;
        if (cur < max) {
            out->v = max;
            changed = 1;
        } else {
            min = b - 0x5000;
            if (cur > min) {
                out->v = min;
                changed = 1;
            }
        }
    }

    c = in->c;
    d = in->d;
    diff_y = d - c;
    if (diff_y <= 0x7000) {
        out->w = (d + c) >> 1;
        changed = 1;
    } else {
        max_y = c + 0x2000;
        cur_y = out->w;
        if (cur_y < max_y) {
            out->w = max_y;
            changed = 1;
        } else {
            min_y = d - 0x5000;
            if (cur_y > min_y) {
                out->w = min_y;
                changed = 1;
            }
        }
    }

    return changed;
}
