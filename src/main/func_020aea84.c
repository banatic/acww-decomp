/* func_020aea84 @ 0x020aea84, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020aea84 {
    u8 pad_00[3];
    u8 unk_03;
};

extern int data_021f395c;

extern int func_020ad798(void);
extern int func_020af9f0(void *);
extern void *func_020af898(void *);
extern void *func_0204e414(void);
extern void *func_0204f694(void *, int);
extern void *func_02037e0c(void *, int, int, int);
extern int func_0204bba8(void *);
extern u16 func_0204bb68(void *);
extern int func_02037e44(void *, u16 *, int, int, int);
extern void func_020af004(void *, void *);
extern int func_020afc84(u32 *);
extern void func_0209e474(u32 *);
extern void func_020afcd4(void);
extern struct UnkStruct_020aea84 *func_020afad4(void *);
extern void func_020af3a0(void *, int);

int func_020aea84(void)
{
    void *m;
    void *g;
    void *t;
    void *c;
    u16 buf[2];
    u32 a[2];
    u32 b[2];
    u32 y;
    u32 x;

    if (func_020ad798() == 1) {
        return 0;
    }
    if (func_020af9f0(&data_021f395c) != 0) {
        g = func_020af898(&data_021f395c);
        m = func_0204e414();
        if (m != 0) {
            t = func_0204f694(m, 2);
            if (t != 0) {
                for (y = 0; y < 0x10; y++) {
                    for (x = 0; x < 0x10; x++) {
                        c = func_02037e0c(t, x, y, 0);
                        if (c == 0) {
                            continue;
                        }
                        if (func_0204bba8(c) == 0) {
                            continue;
                        }
                        buf[0] = func_0204bb68(g);
                        func_02037e44(t, buf, x, y, 0);
                        func_020af004(&data_021f395c, g);
                        a[0] = 0;
                        a[1] = 0;
                        if (func_020afc84(a) != 0) {
                            b[0] = 0;
                            b[1] = 0;
                            func_0209e474(b);
                            if (((u8 *) b)[5] == ((u8 *) a)[5] && ((u8 *) b)[4] == ((u8 *) a)[4] &&
                                ((u8 *) b)[3] == ((u8 *) a)[3]) {
                                func_020afcd4();
                            }
                        }
                        func_020afad4(&data_021f395c)->unk_03 = 0;
                        func_020af3a0(&data_021f395c, 1);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
