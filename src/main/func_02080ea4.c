/* func_02080ea4 @ 0x02080ea4, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02080ea4 {
    int unk_00;
    int w1;
};
struct OBJ {
    int d[16];
};

extern void *func_0208150c(unsigned int);
extern void *func_020984e8(void);
extern int func_02003704(void *);
extern void *func_02099870(void *);
extern int func_020951bc(void *);
extern int func_02094ffc(void *);
extern int func_02099020(void *, int);
extern void func_0209e474(struct UnkStruct_02080ea4 *);
extern void MI_CpuCopy8(const void *, void *, int);
extern int func_0203fc78(int, struct UnkStruct_02080ea4 *, int);
extern void *func_020807a8(void *, void *);
extern int func_02081d20(signed char *);
extern int func_020818d4(void *);
extern void *func_020b5630(struct OBJ *);
extern int func_020b45d0(struct OBJ *, int, int, int, int, int);
extern int func_0203d7c4(int, struct OBJ *);
extern int func_020644cc(int);
extern int func_0205a240(void *, int, void *, void *, int, int);
extern void func_020818fc(void *);
extern void *func_020b5618(struct OBJ *);
extern u8 data_020e197c[];

void func_02080ea4(void *a0, void *a1, void *a2)
{
    struct UnkStruct_02080ea4 s;
    struct UnkStruct_02080ea4 s2;
    struct OBJ obj;
    void *h;
    void *m;
    void *w;
    int ok;

    h = func_0208150c((unsigned int) a0);
    if (a1 == 0) {
        a1 = func_020984e8();
    }
    if (func_02003704(h) == 0) {
        return;
    }
    if (a1 == 0) {
        return;
    }
    m = func_02099870(a1);
    if (func_020951bc(m) == 0) {
        return;
    }
    if (func_02094ffc(m) != 0) {
        return;
    }
    if (func_02099020(a1, 1) != 0) {
        return;
    }
    ok = 0;
    s.unk_00 = 0;
    s.w1 = 0;
    if (a2 == 0) {
        func_0209e474(&s);
    } else {
        MI_CpuCopy8(a2, &s, 8);
    }
    MI_CpuCopy8(&s, &s2, 8);
    if (func_0203fc78(0x13, &s2, 0) ? 1 : 0) {
        if (((u8 *) &s)[2] >= 6) {
            ok = 1;
        }
    }
    if (ok == 0) {
        return;
    }
    w = func_020807a8(a0, m);
    if (w == 0) {
        return;
    }
    if (func_02081d20(w) < 0x40) {
        return;
    }
    if (func_020818d4(w) != 0) {
        return;
    }
    func_020b5630(&obj);
    func_020b45d0(&obj, ((u8 *) &s)[5] + 0x7d0, 4, 0, 0, 0);
    func_0203d7c4(2, &obj);
    if (func_0205a240(data_020e197c, (u8) func_020644cc(3), m, h, 0, 2) != 0) {
        func_020818fc(w);
    }
    func_020b5618(&obj);
}
