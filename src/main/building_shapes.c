/* building_shapes: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3f44 @ 0x020b3f44, 0x14 bytes, Thumb
 * func_020b3f2c @ 0x020b3f2c, 0x18 bytes, Thumb
 * func_020b3f08 @ 0x020b3f08, 0x22 bytes, Thumb
 * func_020b3ed4 @ 0x020b3ed4, 0x32 bytes, Thumb
 * func_020b3eb8 @ 0x020b3eb8, 0x1c bytes, Thumb
 * func_020b3e8c @ 0x020b3e8c, 0x2c bytes, Thumb
 * func_020b3e58 @ 0x020b3e58, 0x32 bytes, Thumb
 * func_020b3e08 @ 0x020b3e08, 0x50 bytes, Thumb
 * func_020b3db8 @ 0x020b3db8, 0x4e bytes, Thumb
 * func_020b3d90 @ 0x020b3d90, 0x28 bytes, Thumb
 * func_020b3d04 @ 0x020b3d04, 0x8a bytes, Thumb
 * func_020b3c58 @ 0x020b3c58, 0xac bytes, Thumb
 * func_020b3bd4 @ 0x020b3bd4, 0x84 bytes, Thumb
 * func_020b3ba0 @ 0x020b3ba0, 0x34 bytes, Thumb
 * func_020b3b50 @ 0x020b3b50, 0x50 bytes, Thumb
 */

#include "types.h"

struct Entry {
    char type;
    char pad_01[3];
};

typedef struct {
    signed char c;
    unsigned char pad_01[3];
} Entry;

typedef struct {
    u32 unk_00[3];
} Vec3;

typedef struct {
    u32 unk_00[9];
} Rec;

extern void *func_02064b2c(const char *, int, int, int);
extern int func_02064328(void *, const char *, int);
extern int NNS_FndMountArchive(void *, const char *, void *);
extern int func_0210285c(void *);
extern int NNS_FndGetArchiveFileByName(void *);
extern const char data_020e5110[];
extern int data_021fbe94;
extern void *data_021f4b44;
extern const char data_020e5120[];
extern const char data_020e5124[];
extern int data_021f4bf4[];
extern void func_020e9898(int);

int func_020b3e58(void *a, int *b, int *c, unsigned int d);

int func_020b3f44(char *p)
{
    int offset = 0;
    int i = 0;
    while (p[offset] == 'M') {
        p += 4;
        i++;
    }
    return i;
}

int func_020b3f2c(struct Entry *p)
{
    int count = 0;
    while (p->type == 'R' || p->type == 'M') {
        p++;
        count++;
    }
    return count;
}

int func_020b3f08(char *p)
{
    char *ptr = p + 4 * func_020b3f2c((struct Entry *) p);
    int i = 0;
    while (*ptr == 'F') {
        ptr += 4;
        i++;
    }
    return i;
}

int func_020b3ed4(Entry *arg)
{
    int i, j, count, offset;
    Entry *p;

    i = func_020b3f2c((struct Entry *) arg);
    j = func_020b3f08((char *) arg);
    p = arg + i;
    p += j;
    count = 0;
    offset = count;
    while (p[offset].c == 'S') {
        p++;
        count++;
    }
    return count;
}

int func_020b3eb8(int param)
{
    int a;
    int b;
    int result;

    a = func_020b3f08((char *) param);
    b = func_020b3ed4((Entry *) param);
    result = a + b;
    return result;
}

int func_020b3e8c(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    if (d < (unsigned int) func_020b3f44((char *) a)) {
        return (unsigned int) func_020b3e58((void *) a, (int *) b, (int *) c, d);
    } else {
        return 0;
    }
}

int func_020b3e58(void *a, int *b, int *c, unsigned int d)
{
    if (d < (unsigned int) func_020b3f2c((struct Entry *) a)) {
        char *base = (char *) a + (d << 2);
        *b = *(signed char *) (base + 2);
        *c = *(signed char *) (base + 3);
        return 1;
    } else {
        return 0;
    }
}

int func_020b3e08(int *p, int *a, int *b, unsigned int idx)
{
    int *base;
    unsigned int n;
    int *e;

    base = p + (unsigned int) func_020b3f2c((struct Entry *) p);
    n = (unsigned int) func_020b3eb8((int) p);

    if (idx < n) {
        e = base + idx;
        *a = ((signed char *) e)[2];
        *b = ((signed char *) e)[3];

        if (*a == 0 && *b == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int func_020b3db8(char *a, int *b, int *c, int *d, unsigned int e)
{
    char *base = a + (unsigned int) func_020b3f2c((struct Entry *) a) * 4;
    char *entry;
    unsigned int index;

    if (e < (unsigned int) func_020b3ed4((Entry *) a)) {
        index = (unsigned int) func_020b3f08(a);
        index += e;
        entry = base + index * 4;
        *b = entry[1];
        *c = entry[2];
        *d = entry[3];
        return 1;
    }
    return 0;
}

int func_020b3d90(int *p)
{
    int a, b;
    a = func_020b3f08((char *) p);
    b = func_020b3f2c((struct Entry *) p);
    return p[a + (b + func_020b3ed4((Entry *) p)) + 1];
}

int func_020b3d04(void *base, Vec3 *out1, Vec3 *out2, Vec3 *out3, u32 idx)
{
    u32 cnt = (u32) func_020b3d90((int *) base);
    out1->unk_00[0] = 0;
    out1->unk_00[1] = 0;
    out1->unk_00[2] = 0;
    out2->unk_00[0] = 0;
    out2->unk_00[1] = 0;
    out2->unk_00[2] = 0;
    out3->unk_00[0] = 0;
    out3->unk_00[1] = 0;
    out3->unk_00[2] = 0;
    if (idx < cnt) {
        u32 v0 = (u32) func_020b3f08((char *) base);
        u32 v1 = (u32) func_020b3f2c((struct Entry *) base);
        u32 v2 = (u32) func_020b3ed4((Entry *) base);
        u32 off = 4 * (v0 + (v1 + v2) + 1) + 4;
        Rec *rec = (Rec *) ((char *) base + off);
        Rec *p = rec + idx;
        out1->unk_00[0] = rec[idx].unk_00[0];
        out1->unk_00[1] = p->unk_00[1];
        out1->unk_00[2] = p->unk_00[2];
        out2->unk_00[0] = p->unk_00[3];
        out2->unk_00[1] = p->unk_00[4];
        out2->unk_00[2] = p->unk_00[5];
        out3->unk_00[0] = p->unk_00[6];
        out3->unk_00[1] = p->unk_00[7];
        out3->unk_00[2] = p->unk_00[8];
        return 1;
    }
    return 0;
}

void func_020b3c58(void *obj, int *ocx, int *ocy, int *ow, int *oh)
{
    int minx, maxx, miny, maxy;
    unsigned int n;
    unsigned int i;
    int a, b, c;
    int t, y1, y0, x1, x0;

    maxx = 0;
    minx = 0;
    maxy = 0;
    miny = 0;
    n = (unsigned int) func_020b3ed4((Entry *) obj);
    if (n != 0) {
        maxx = -1;
        minx = 1;
        maxy = -1;
        miny = 1;
        for (i = 0; i < n; i++) {
            if (func_020b3db8((char *) obj, &a, &b, &c, i) != 0) {
                if (b < minx) {
                    minx = b;
                }
                if (c < miny) {
                    miny = c;
                }
                if (b > maxx) {
                    maxx = b;
                }
                if (c > maxy) {
                    maxy = c;
                }
            }
        }
    }
    x1 = (maxx << 13) + 0x1000;
    x0 = (minx << 13) - 0x1000;
    y1 = (maxy << 13) + 0x1000;
    y0 = (miny << 13) - 0x1000;
    *ocx = (x1 + x0) >> 1;
    *ocy = (y1 + y0) >> 1;
    t = x1 - x0;
    if (t < 0) {
        t = -t;
    }
    *ow = t;
    t = y1 - y0;
    if (t < 0) {
        t = -t;
    }
    *oh = t;
}

void func_020b3bd4(void)
{
    u8 name[0x20];
    u8 file[0x6c];
    unsigned int i;
    void *p;

    p = func_02064b2c(data_020e5110, data_021fbe94, 4, 0);
    data_021f4b44 = p;
    if (p != 0) {
        if (NNS_FndMountArchive(file, data_020e5120, p) != 0) {
            for (i = 0; i < 0x22; i++) {
                func_02064328(name, data_020e5124, i);
                data_021f4bf4[i] = NNS_FndGetArchiveFileByName(name);
            }
            func_0210285c(file);
        }
    } else {
        for (i = 0; i < 0x22; i++) {
            data_021f4bf4[i] = 0;
        }
    }
}

void func_020b3ba0(void)
{
    int condition_value0;
    unsigned int i;

    for (i = 0; i < 34; i++) {
        ((unsigned int *) data_021f4bf4)[i] = 0;
    }

    if ((condition_value0 = (int) (data_021f4b44))) {
        func_020e9898(condition_value0);
        data_021f4b44 = 0;
    }
}

void *func_020b3b50(unsigned short *p)
{
    unsigned int v;
    int flag;

    if (data_021f4b44 != 0) {
        flag = 0;
        v = *p;
        if (v >= 0x5000 && v <= 0x5021) {
            flag = 1;
        }

        if (flag) {
            v &= 0xfff;
        } else {
            v = -1;
        }

        if (v != -1) {
            return ((void * *) data_021f4bf4)[v];
        }
    }
    return 0;
}
