/* func_ov003_0222f570 @ 0x0222f570, 0x10c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222f570;
extern UnkStruct_0222f570 *data_020ccf94;

struct UnkStruct_0222f570_2 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual int hit();
};

extern "C" {

extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_02096614(int *a, int *b, int *c, int d, int e);
extern int func_ov003_02219e58(int i);
extern int func_020ea990(int *a, void *b);
extern void *func_020961a8(int i);
extern UnkStruct_0222f570_2 *func_02082654(int i);

void func_ov003_0222f570(int a0, char *self)
{
    int za;
    int zb;
    void *o;
    UnkStruct_0222f570_2 *ob;
    int t[3];
    int q[3];
    u8 i;
    int lim;
    int *p;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        if (func_020a7278() == 0) {
            return;
        }
        i = 0;
        za = 0;
        zb = 0;
        for (; i < 4; i++) {
            if (func_02096614(&t[0], &t[1], &t[2], -1, i) != 0 && *(u8 *) &t[0] == 0 && func_ov003_02219e58(i) != 0) {
                q[0] = t[1];
                q[1] = za;
                q[2] = t[2];
                lim = *(int *) (self + 0x224);
                if ((func_020ea990((int *) (self + 0x204), q) < lim ? 1 : zb) != 0) {
                    *(u8 *) (self + 0x254) = 0xfe;
                }
            }
        }
    } else if (func_ov003_02219e58(4) != 0) {
        o = func_020961a8(4);
        if (o != 0) {
            lim = *(int *) (self + 0x224);
            if (func_020ea990((int *) (self + 0x204), (char *) o + 0x5c) < lim) {
                *(u8 *) (self + 0x254) = 0xfe;
            }
        }
    } else {
        p = (int *) (self + 0x204);
        for (i = 0; i < 8; i++) {
            ob = func_02082654(i);
            if (ob != 0) {
                lim = *(int *) (self + 0x224);
                if (func_020ea990(p, (char *) ob + 0x5c) < lim && ob->hit() != 0) {
                    *(u8 *) (self + 0x254) = 0xfe;
                }
            }
        }
    }
}
}
