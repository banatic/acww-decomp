/* acre_tile_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204f800 @ 0x0204f800, 0x18 bytes, Thumb
 * func_0204f7e0 @ 0x0204f7e0, 0x20 bytes, Thumb
 * func_0204f7ac @ 0x0204f7ac, 0x34 bytes, Thumb
 * func_0204f794 @ 0x0204f794, 0x18 bytes, Thumb
 * func_0204f778 @ 0x0204f778, 0x1c bytes, Thumb
 * func_0204f704 @ 0x0204f704, 0x72 bytes, Thumb
 * func_0204f694 @ 0x0204f694, 0x6e bytes, Thumb
 * func_0204f658 @ 0x0204f658, 0x3a bytes, Thumb
 * func_0204f61c @ 0x0204f61c, 0x3c bytes, Thumb
 * func_0204f5e0 @ 0x0204f5e0, 0x3c bytes, Thumb
 */

struct UnkStruct_0204f7e0 {
    int pad_00;
    int y;
};

struct UnkStruct_0204f7e0_2 {
    int x;
    int y;
    int z;
};

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} UnkStruct_0204f794;

typedef struct {
    unsigned int w;
    unsigned int h;
} Dim;

typedef struct {
    void *data;
    Dim dim;
} SInfo;

typedef struct {
    void *data;          // offset 0
    unsigned int width;  // offset 4
    unsigned int height; // offset 8
} UnkStruct_0204f658;

struct UnkStruct_0204f61c {
    void *data;
    unsigned int width;
    unsigned int height;
};

struct Grid {
    void *data;
    unsigned int width;
    unsigned int height;
};

extern int func_02037d80(void *cell, void *arg);
extern int func_02037d64(void *cell, void *arg);
extern void *func_02037d9c(void *);
extern void *func_02037e0c(void *p, int a, int b, unsigned char c);

void func_0204f794(UnkStruct_0204f794 *p, unsigned int a, unsigned int b);

void func_0204f800(int *out_x, int *out_y, int x, int y, int offset_x, int offset_y)
{
    *out_x = (x << 4) + offset_x;
    *out_y = (y << 4) + offset_y;
}

void func_0204f7e0(struct UnkStruct_0204f7e0 *a, struct UnkStruct_0204f7e0_2 *b)
{
    func_0204f794((UnkStruct_0204f794 *) a, b->x >> 13, b->z >> 13);
    a->y = b->y;
}

void func_0204f7ac(int a, int b, int c, int d, int e)
{
    struct {
        int x;
        int y;
    } local;

    local.x = 0;
    local.y = 0;
    func_0204f800(&local.x, &local.y, b, c, d, e);
    func_0204f794((UnkStruct_0204f794 *) a, local.x, local.y);
}

void func_0204f794(UnkStruct_0204f794 *p, unsigned int a, unsigned int b)
{
    p->x = (a << 13) + 0x1000;
    p->z = (b << 13) + 0x1000;
    p->y = 0;
}

void func_0204f778(unsigned int *p, unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    p[0] = a << 17;
    p[2] = b << 17;
    p[0] += c << 13;
    p[2] += d << 13;
}

void *func_0204f704(SInfo *s, void *arg)
{
    int x, y;
    int w, h;
    int x0;
    void *nullp;
    void *c;
    Dim *dp;

    if (arg == 0) {
        goto zero;
    }
    dp = &s->dim;
    w = dp->w;
    h = dp->h;
    x0 = 0;
    nullp = 0;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            if ((unsigned int) x < s->dim.w && (unsigned int) y < s->dim.h && s->data != 0) {
                c = (char *) s->data + (x + y * s->dim.w) * 0x28;
            } else {
                c = nullp;
            }
            if (c != 0) {
                if (func_02037d80(c, arg) != 0) {
                    return c;
                }
            }
        }
    }
zero:
    return 0;
}

void *func_0204f694(SInfo *s, void *arg)
{
    int x, y;
    int w, h;
    int x0;
    void *nullp;
    void *c;
    Dim *dp;

    dp = &s->dim;
    w = dp->w;
    h = dp->h;
    x0 = 0;
    nullp = 0;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            if ((unsigned int) x < s->dim.w && (unsigned int) y < s->dim.h && s->data != 0) {
                c = (char *) s->data + (x + y * s->dim.w) * 0x28;
            } else {
                c = nullp;
            }
            if (c != 0) {
                if (func_02037d64(c, arg) != 0) {
                    return c;
                }
            }
        }
    }
    return 0;
}

void *func_0204f658(UnkStruct_0204f658 *a, unsigned int x, unsigned int y)
{
    void *ret = 0;
    void *p;
    if (x < a->width && y < a->height && a->data) {
        p = (char *) a->data + (x + y * a->width) * 40;
    } else {
        p = 0;
    }
    if (p) {
        ret = func_02037d9c(p);
    }
    return ret;
}

void *func_0204f61c(struct UnkStruct_0204f61c *s, unsigned int x, unsigned int y, unsigned int z)
{
    void *result;
    void *ret;

    if (x < s->width && y < s->height && s->data != 0) {
        result = (void *) ((char *) s->data + (x + y * s->width) * 40);
    } else {
        result = 0;
    }

    ret = 0;
    if (result != 0) {
        ret = (void *) func_02037d80(result, (void *) z);
    }
    return ret;
}

void *func_0204f5e0(struct Grid *grid, unsigned int x, unsigned int y, int p3, int p4, unsigned char p5)
{
    void *ptr;

    if (x < grid->width && y < grid->height && grid->data != 0) {
        ptr = (void *) ((char *) grid->data + (x + y * grid->width) * 0x28);
    } else {
        ptr = 0;
    }

    if (ptr) {
        return func_02037e0c(ptr, p3, p4, p5);
    }
    return ptr;
}
