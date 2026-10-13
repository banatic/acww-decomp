/* func_0205a554 @ 0x0205a554, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0205a554 {
    u8 d[0x40];
} UnkStruct_0205a554;
typedef struct UnkStruct_0205a554_2 {
    u8 d[0x28];
} UnkStruct_0205a554_2;
typedef struct UnkStruct_0205a554_3 {
    u8 d[0x5c];
} UnkStruct_0205a554_3;
typedef struct UnkStruct_0205a554_4 {
    u8 d[0x100];
} UnkStruct_0205a554_4;

extern void func_020b5630(UnkStruct_0205a554 *a);
extern void func_020b5618(UnkStruct_0205a554 *a);
extern int func_020b45d0(UnkStruct_0205a554 *a, void *x, int n, int e, int f, int h);
extern void func_0203d7c4(int slot, void *obj);
extern void func_02062f64(UnkStruct_0205a554_2 *b, void *x);
extern void func_02062f4c(UnkStruct_0205a554_2 *b);
extern void func_020a8228(UnkStruct_0205a554_3 *c);
extern void func_020a8210(UnkStruct_0205a554_3 *c);
extern void func_020b49d4(UnkStruct_0205a554_3 *c, u8 *s, void *t);
extern void func_02066694(UnkStruct_0205a554_4 *d);
extern void func_02066688(UnkStruct_0205a554_4 *d);
extern void func_02066024(UnkStruct_0205a554_4 *d, u8 *s, void *t, void *u, void *v, int w);
extern void func_02097a54(UnkStruct_0205a554_4 *d);
extern void *func_02098844(void *tbl, int i);
extern int func_02099a28(void);
extern s16 *func_0209d358(int v, int k);
extern int func_02099020(void *o, int k);
extern int func_02099870(void *o);
extern u8 data_021dc7bc[];
extern u8 data_020dd3e8[];
extern u8 data_020dd384[];
extern u8 data_020dd3d8[];
extern u8 data_020dd390[];

int func_0205a554(int a1, int a2, void *a3, void *a4, int a5)
{
    int v;
    u8 buf[4];
    UnkStruct_0205a554 oa;
    UnkStruct_0205a554_2 ob;
    int i;
    void *o;

    func_020b5630(&oa);
    if (func_020b45d0(&oa, a3, 0xa, 0, 0, 0) != 0) {
        func_0203d7c4(1, &oa);
        func_02062f64(&ob, a4);
        func_0203d7c4(2, &ob);
        if (a5 < 4) {
            UnkStruct_0205a554_3 oc;
            func_020a8228(&oc);
            buf[1] = (u8) a5;
            func_020b49d4(&oc, &buf[1], data_020dd3e8);
            func_0203d7c4(3, &oc);
            func_020a8210(&oc);
        }
        v = 0;
        for (i = 0; i < 4; i++) {
            o = func_02098844(data_021dc7bc, i);
            if (o != 0 && func_02099a28() != 0 && (*func_0209d358(v, 0x22) != 0 || func_02099020(o, 0xe) != 0)) {
                UnkStruct_0205a554_4 od;
                func_02066694(&od);
                buf[0] = (u8) a2;
                func_02066024(&od, buf, data_020dd3d8, data_020dd390, data_020dd384, func_02099870(o));
                func_02097a54(&od);
                func_02066688(&od);
            }
        }
        func_02062f4c(&ob);
        func_020b5618(&oa);
        return 1;
    } else {
        func_020b5618(&oa);
        return 0;
    }
}
