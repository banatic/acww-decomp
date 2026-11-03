/* scene_share_table: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02085148 @ 0x02085148, 0x2c bytes, Thumb
 * func_020850e8 @ 0x020850e8, 0x60 bytes, Thumb
 * func_020850b8 @ 0x020850b8, 0x2e bytes, Thumb
 * func_02084f8c @ 0x02084f8c, 0x12c bytes, Thumb
 */

struct UnkStruct_020850e8 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_02084f8c {
    char pad_00[0x64];
    int unk_64;
};

extern int func_020852e4(unsigned short *param);
extern int func_020851e0(unsigned short *param);
extern int func_02085174(void *p, int, int);
extern int func_02073dd4(void *p, int field);
extern void func_020771cc(int a, void *b, int c, int d);
extern struct UnkStruct_020850e8 *data_020ccf94;
extern int func_020b65c4(void);
extern void func_02077a34(int, void *, int);

int func_02085148(unsigned short *param)
{
    int nibble = (*param & 0xF000) >> 12;
    if (nibble == 0xE) {
        return func_020852e4(param);
    } else if (nibble == 0xD) {
        return func_020851e0(param);
    }
    return 0;
}

void func_020850e8(int x, int y, int z, unsigned short *p)
{
    func_02085174(p, y, z);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
        unsigned short val = *p;
        int high = (val & 0xf000) >> 12;
        int low = val & 0xfff;
        if (high == 0xe) {
            low += 0xc;
            func_020771cc(low, &x, 0, 0);
        } else if (high == 0xd) {
            low += 0x20;
            func_020771cc(low, &x, 0, 0);
        }
    }
}

int func_020850b8(int *out0, int *out1, unsigned short *p2)
{
    unsigned char *ret = (unsigned char *) func_02085148(p2);
    if (ret != 0 && ret[0] != 0) {
        *out0 = ret[1];
        *out1 = ret[2];
        return 1;
    }
    return 0;
}

void func_02084f8c(void)
{
    struct {
        unsigned char b;
        unsigned short h;
    } d;
    int v1;
    int v2;
    int i;
    int idx;
    int ret;
    int c;
    struct UnkStruct_02084f8c *g;

    c = func_020b65c4();
    v1 = 4;
    v2 = 4;
    d.h = 0xfff1;
    i = 0;
    g = (*(struct UnkStruct_02084f8c * *) &data_020ccf94);
    idx = i;

    do {
        d.h = (i & 0xfff) | 0xe000;
        ret = func_02085148((unsigned short *) (&d.h));
        if (ret) {
            func_02077a34(ret + 3, &d, idx);
            if (d.b == c) {
                v1 = 4;
                v2 = 4;
                if (func_020850b8(&v1, &v2, (unsigned short *) (&d.h))) {
                    if (v2 >= 4) {
                        func_020850e8(1, 4, 4, (unsigned short *) (&d.h));
                    } else {
                        int field = g->unk_64;
                        if (v2 == field && v2 != v1) {
                            func_020850e8(1, field, 4, (unsigned short *) (&d.h));
                        }
                    }
                }
            }
        }
        i++;
    } while (i < 8);

    i = 0;
    idx = i;

    do {
        d.h = (i & 0xfff) | 0xd000;
        ret = func_02085148((unsigned short *) (&d.h));
        if (ret) {
            func_02077a34(ret + 3, &d, idx);
            if (d.b == c) {
                v1 = 4;
                v2 = 4;
                if (func_020850b8(&v1, &v2, (unsigned short *) (&d.h))) {
                    if (v2 >= 4) {
                        func_020850e8(1, 4, 4, (unsigned short *) (&d.h));
                    } else {
                        int field = g->unk_64;
                        if (v2 == field && v2 != v1) {
                            func_020850e8(1, field, 4, (unsigned short *) (&d.h));
                        }
                    }
                }
            }
        }
        i++;
    } while (i < 0x26);
}
