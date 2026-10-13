/* func_ov004_02220834 @ 0x02220834, 0x180 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct OUT {
    void *unk_00;
    u8 unk_04;
};

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void *func_020984e8(void);
extern void *func_02099870(void *p);
extern int func_020804b8(void *a, void *b);
extern void func_02081e14(int r, int a, int b, int c);
extern void *func_0208150c(void *p);
extern void func_0200366c(void *a, void *b, int n, void *c);
extern int func_020644cc(int n);
extern void func_02015de4(void *self, void *p, int a, int b);
extern char data_ov004_02257e40[];
extern char data_ov004_02253ee4[];
extern char data_ov004_02253ed0[];
extern char data_ov004_02253ef0[];

static __inline int chk(u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

void func_ov004_02220834(void *self, struct OUT *out)
{
    // DECLS
    int res;
    void *g;
    unsigned int st;
    u16 *p;
    // ENDDECLS

    res = func_020804b8(*(void **) ((char *) *(void **) ((char *) self + 0x1a4) + 0x830), func_02099870(func_020984e8()));
    if (res != 0) {
        func_02081e14(res, 0, 0, 0);
    }
    g = *(void **) ((char *) self + 0x1a4);
    st = *(u8 *) ((char *) g + 0xac8);
    if (st == 5) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ee4);
        out->unk_00 = data_ov004_02257e40;
        out->unk_04 = (u8) func_020644cc(3);
    } else if (st == 3) {
        func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
        out->unk_00 = data_ov004_02257e40;
        out->unk_04 = (u8) (func_020644cc(2) + 2);
    } else {
        switch (st) {
            case 0:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ef0);
                out->unk_04 = (u8) func_020644cc(3);
                break;
            case 1:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
                out->unk_04 = (u8) func_020644cc(2);
                break;
            case 2:
                func_0200366c(func_0208150c(*(void **) ((char *) g + 0x830)), data_ov004_02257e40, 0x28, data_ov004_02253ed0);
                p = (u16 *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898);
                if (chk(p, 0xfff1) || *(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x914) == 5) {
                    out->unk_04 = (u8) (func_020644cc(2) + 4);
                } else {
                    func_02015de4(self, (char *) *(void **) ((char *) self + 0x1a4) + 0x898, 0, 7);
                    out->unk_04 = (u8) (func_020644cc(2) + 6);
                }
                break;
        }
        out->unk_00 = data_ov004_02257e40;
    }
}
