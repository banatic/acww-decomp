/* town_growth_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020493b4 @ 0x020493b4, 0x20 bytes, Thumb
 * func_02049384 @ 0x02049384, 0x30 bytes, Thumb
 * func_0204930c @ 0x0204930c, 0x78 bytes, Thumb
 * func_020492c8 @ 0x020492c8, 0x44 bytes, Thumb
 */

struct Entry {
    int x;
    int y;
};

struct UnkStruct_02049384 {
    unsigned int header;
    unsigned int count;
    struct Entry entries[64];
    unsigned short shorts[1];
};

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

extern int func_0204e414(void);
extern int func_020644cc(int);
extern void func_0204a198(int, unsigned short, int, int);

void func_020493b4(unsigned int *r0, unsigned char *r1, int r2, int r3)
{
    int i;
    unsigned int val;
    unsigned int *p;

    r1 = r1 + (r2 << 1) + r3;
    *r0 = r1[4];
    r0[1] = 0;
    val = 0xFFFFFFFF;
    for (i = 0; i < 0x40; i++) {
        p = r0 + (i << 1);
        p[2] = val;
        p[3] = val;
    }
}

void func_02049384(struct UnkStruct_02049384 *obj, unsigned short value, int a, int b)
{
    obj->shorts[obj->count] = value;
    obj->entries[obj->count].x = a;
    obj->entries[obj->count].y = b;
    obj->count++;
}

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

void func_020492c8(void *base, int arg)
{
    int i = 0;
    int j;

    for (j = 0; j < 2; j++) {
        i = 0;
        do {
            func_020493b4((unsigned int *) ((char *) base + i * 0x510 + j * 0x288), (unsigned char *) arg, i, j);
            i++;
        } while (i < 2);
    }
}
