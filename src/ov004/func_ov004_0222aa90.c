/* func_ov004_0222aa90 @ 0x0222aa90, 0x194 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222aa90 {
    int unk_00;
    u8 unk_04;
    u8 unk_05;
};
struct UnkStruct_0222aa90_2 {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    int unk_04;
};

extern void func_0204f794(void *p, int a, int b);
extern int func_ov004_0223c5a4(void *p);
extern u16 *func_0204f5a8(void *g, void *p, int k);
extern int func_02008258(void *self, int a);
extern void func_0200d4e8(void *self, int a, int b, int c);
extern int func_02099fe8(void);
extern int func_020b67d4(void);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern unsigned int func_020b2300(void);
extern void func_0200f27c(void *self, int a);
extern void func_02045f08(int *p, int a);
extern void func_ov004_0223bb20(int v, u16 *a, u16 *b);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f328(void *self, int a);
extern void *data_021c80bc;

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

void func_ov004_0222aa90(void *self, void *msg)
{
    // DECLS
    struct UnkStruct_0222aa90_2 *m;
    int v;
    struct UnkStruct_0222aa90 *o;
    int b;
    int c;
    u16 *r;
    // ENDDECLS
    int arr[2];

    m = (struct UnkStruct_0222aa90_2 *) ((char *) msg + 0xc);
    v = m->unk_04;
    o = (struct UnkStruct_0222aa90 *) ((char *) self + 0x7d4);
    o->unk_04 = 0;
    o->unk_05 = 0;
    o->unk_00 = v;
    b = *(u8 *) ((char *) msg + 0xc);
    c = m->unk_01;
    func_0204f794((char *) self + 0x824, b, c);
    *(int *) ((char *) self + 0x828) = func_ov004_0223c5a4((char *) self + 0x824);
    *(int *) ((char *) self + 0x830) = 0x1000;
    *(int *) ((char *) self + 0x834) = 0x1000;
    *(int *) ((char *) self + 0x838) = 0x1000;
    if (v < 0) {
        r = func_0204f5a8(data_021c80bc, (char *) self + 0x824, 1);
        if (r == 0) {
            *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
        }
        *(u16 *) ((char *) self + 0x822) = *r;
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
    }
    if (func_02099fe8() == -1 && func_020b67d4() != 0 && chk((u16 *) ((char *) self + 0x820), 0xfff1) == 0) {
        func_020109fc(self, 0, 3, 0);
        o->unk_05 = 6;
        *(u16 *) ((char *) self + 0x822) = 0xfff1;
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
        return;
    }
    if (func_020b2300() <= 1) {
        if (v < 0) {
            func_0200f27c(self, 0xd);
            arr[0] = b;
            arr[1] = c;
            func_02045f08(arr, 1);
        } else {
            func_ov004_0223bb20(v, (u16 *) ((char *) self + 0x820), (u16 *) ((char *) self + 0x822));
        }
        func_020109a0(self, 0x19, 3, 0);
        func_0200f328(self, 0x52);
    } else {
        o->unk_05 = 0xa;
        func_020109fc(self, 0, 3, 0);
    }
}
