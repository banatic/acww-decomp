/* func_02084f8c @ 0x02084f8c, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_02085148(const unsigned short *);
extern void func_02077a34(int, void *, int);
extern int func_020850b8(int *, int *, const unsigned short *);
extern void func_020850e8(int, int, int, const unsigned short *);

struct UnkStruct_02084f8c {
    char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_02084f8c *data_020ccf94;

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
    g = data_020ccf94;
    idx = i;

    do {
        d.h = (i & 0xfff) | 0xe000;
        ret = func_02085148(&d.h);
        if (ret) {
            func_02077a34(ret + 3, &d, idx);
            if (d.b == c) {
                v1 = 4;
                v2 = 4;
                if (func_020850b8(&v1, &v2, &d.h)) {
                    if (v2 >= 4) {
                        func_020850e8(1, 4, 4, &d.h);
                    } else {
                        int field = g->unk_64;
                        if (v2 == field && v2 != v1) {
                            func_020850e8(1, field, 4, &d.h);
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
        ret = func_02085148(&d.h);
        if (ret) {
            func_02077a34(ret + 3, &d, idx);
            if (d.b == c) {
                v1 = 4;
                v2 = 4;
                if (func_020850b8(&v1, &v2, &d.h)) {
                    if (v2 >= 4) {
                        func_020850e8(1, 4, 4, &d.h);
                    } else {
                        int field = g->unk_64;
                        if (v2 == field && v2 != v1) {
                            func_020850e8(1, field, 4, &d.h);
                        }
                    }
                }
            }
        }
        i++;
    } while (i < 0x26);
}
