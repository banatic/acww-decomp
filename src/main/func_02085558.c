/* func_02085558 @ 0x02085558, 0x1a4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02085558 {
    int a, b;
} UnkStruct_02085558;
typedef struct Gx {
    char pad_00[0x64];
    int unk_64;
} Gx;
typedef struct UnkStruct_02085558_2 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_02085558_2;

extern void *data_020d0644;
extern int data_021e5a2c[];
extern u8 data_020e54a8;
extern Gx *data_020ccf94;
extern int data_020e1d8c;

extern void *func_0208602c(void);
extern void *func_020860c0(void *);
extern void *func_020860bc(void *);
extern void func_02087e00(void *);
extern void func_02087b10(void *);
extern void func_02087b04(void *);
extern int func_02087e38(void *);
extern void func_02087df4(void *);
extern int func_020b6660(void);
extern void func_0207a964(int *);
extern void func_0207a8ac(int *);
extern void func_02079174(int);
extern int func_020b65b8(void);
extern int func_020b6674(void);
extern int func_020791ec(void);
extern void func_0209e474(UnkStruct_02085558 *);
extern int func_0207aa08(int *, UnkStruct_02085558 *);
extern void func_02079204(int);
extern void func_020791d4(int);
extern int func_02084ad0(void);
extern int func_02073dd4(Gx *, int);
extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern void func_0207a340(int *, void *);
extern void func_02085a30(void *);
extern int func_020b6680(void);
extern void func_020858ac(void *);
extern int func_020b67d4(void);
extern int func_0207af30(void);
extern int func_0207915c(void);
extern void func_020b23c8(void);
extern int func_020b6804(void);
extern void func_020856fc(void *);
extern void func_02084c60(void *);
extern UnkStruct_02085558_2 *func_02084b74(void *, int *, void *);
extern void func_02084210(void *);
extern void func_0207be8c(int *);

int func_02085558(void *self)
{
    UnkStruct_02085558 s;
    void *g6;
    int *w;
    int r;
    int x;
    void *y;
    UnkStruct_02085558_2 *q;
    unsigned int ok;

    g6 = data_020d0644;
    w = data_021e5a2c;
    func_02087e00(func_020860c0(func_0208602c()));
    func_02087b10(func_020860bc(func_0208602c()));
    if (func_020b6660() != 0) {
        if ((int) w != 0) {
            func_0207a964(w);
            func_0207a8ac(w);
        }
        func_02079174(-1);
    } else {
        func_020b65b8();
        if (func_020b6674() != 0) {
            s.a = 0;
            s.b = 0;
            r = func_020791ec();
            func_0209e474(&s);
            if (r != -1) {
                if (r != func_0207aa08(w, &s)) {
                    func_02079204(-1);
                    func_020791d4(-1);
                    if ((int) w != 0) {
                        func_0207a8ac(w);
                    }
                }
            }
        }
    }
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        if (func_02084ad0() == 0) {
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
                if (func_020984e8() != 0) {
                    y = func_02099870(func_020984e8());
                } else {
                    y = 0;
                }
                func_0207a340(w, y);
            }
            func_02085a30(self);
        }
    } else if (func_020b6680() != 0) {
        func_020858ac(self);
    } else if (func_020b67d4() != 0) {
        if ((int) w != 0 && func_0207af30() != 0xa) {
            x = func_0207915c();
            if (x != -1) {
                func_02079174(-1);
                func_020b23c8();
            }
        }
        if (func_020b6804() == 0) {
            func_020856fc(self);
        }
    }
    func_02084c60(self);
    q = func_02084b74(self, &data_020e1d8c, g6);
    if (q != 0) {
        func_02087b04(func_020860bc(func_0208602c()));
        if (q->unk_02 == 0xd008) {
            if (func_02087e38(func_020860c0(func_0208602c())) == 0) {
                goto skip;
            }
        }
        func_02087df4(func_020860c0(func_0208602c()));
    }
skip:
    func_02084210(self);
    if (func_020b6660() != 0) {
        func_0207be8c(w);
    }
    return 1;
}
