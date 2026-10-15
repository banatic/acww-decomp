/* func_02099050 @ 0x02099050, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct OA {
    u8 d[0x20];
} OA;
typedef struct OB {
    u8 d[0x20];
} OB;
typedef struct OC {
    u8 d[0x5c];
} OC;

extern int func_02099870(u8 *p);
extern int func_020951bc(int a);
extern int func_02099df4(u8 *p);
extern void *func_02094fd4(OA *o);
extern void *func_020641c8(OB *o);
extern void *func_020a8228(OC *o);
extern void *func_02095074(int a, OA *o);
extern int func_0203d7c4(int n, void *o);
extern void func_020a8c1c(void *o);
extern int func_02003618(u8 *p, OA *o);
extern int func_0209c54c(int *q, int i);
extern void *func_020b49d4(OC *o, u8 *q, int t);
extern void func_02064210(u8 *p, OB *o);
extern int func_0207d3dc(void *g, int u, int v, int a, u8 *pb, u8 *pc);
extern void func_02099e18(u8 *p);
extern void *func_020a8210(OC *o);
extern void *func_020641b0(OB *o);
extern void *func_02094fbc(OA *o);

extern int data_020e3128;

void func_02099050(u8 *p)
{
    int a;
    int u;
    u8 *pc;
    int t;
    u8 bv;
    int w;
    OA oa;
    OB ob;
    OC oc;
    u8 *pb;
    int v;
    int i;

    a = func_02099870(p);
    if (func_020951bc(a)) {
        if (func_02099df4(p + 0x245c)) {
            pb = p + 0x246a;
            pc = p + 0x247a;
            func_02094fd4(&oa);
            func_020641c8(&ob);
            func_020a8228(&oc);
            u = 0;
            v = 10;
            w = 0;
            if (*(u16 *) (p + 0x247a) != 0xfff1) {
                u = v;
                v = 5;
            }
            func_02095074(a, &oa);
            func_0203d7c4(0, &oa);
            func_020a8c1c(&oa);
            func_02003618(pb, &oa);
            func_0203d7c4(1, &oa);
            for (i = 0; i < 6; i++) {
                t = func_0209c54c(&w, i);
                func_020a8c1c(&oc);
                bv = (u8) w;
                func_020b49d4(&oc, &bv, t);
                func_0203d7c4(i + 2, &oc);
            }
            func_02064210(p + 0x245c, &ob);
            func_0203d7c4(8, &ob);
            if (func_0207d3dc(&data_020e3128, u, v, a, pb, pc)) {
                func_02099e18(p + 0x245c);
            }
            func_020a8210(&oc);
            func_020641b0(&ob);
            func_02094fbc(&oa);
        }
    }
}
