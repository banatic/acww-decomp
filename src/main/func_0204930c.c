/* func_0204930c @ 0x0204930c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_020644cc(int);
extern void func_0204a198(int, unsigned short, int, int);

struct UnkStruct_0204930c {
    int a;
    int b;
};

struct State {
    int total;
    int active;
    struct UnkStruct_0204930c items[64];
    unsigned short shorts[64];
};

void func_0204930c(struct State *s)
{
    int n, v0, cap, v1, i, remaining;

    if (s->total < 7) {
        return;
    }

    n = s->total - 6;
    if (n > s->active) {
        n = s->active;
    }

    v0 = func_0204e414();
    cap = s->active;
    v1 = -1;

    while (n != 0) {
        remaining = func_020644cc(s->active);
        for (i = 0; i < cap; i++) {
            if (s->items[i].a < 0) {
                continue;
            }
            if (--remaining >= 0) {
                continue;
            }
            func_0204a198(v0, s->shorts[i], s->items[i].a, s->items[i].b);
            s->items[i].a = v1;
            s->items[i].b = v1;
            s->active--;
            break;
        }
        n--;
    }
}
