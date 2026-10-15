/* func_02080dc0 @ 0x02080dc0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02080dc0 {
    u8 pad_00[0x20];
} UnkStruct_02080dc0;
typedef struct UnkStruct_02080dc0_2 {
    u16 unk_00;
} UnkStruct_02080dc0_2;
typedef struct UnkStruct_021dc7a8 {
    u16 unk_00;
    UnkStruct_02080dc0_2 unk_02;
} UnkStruct_021dc7a8;

extern UnkStruct_021dc7a8 data_021dc7a8;
extern int data_020e1974;

extern int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern void *func_02099870(void *p);
extern int func_020951bc(void *);
extern int func_02094ffc(void *p);
extern int func_020807a8(void *a, void *p);
extern void *func_020641c8(UnkStruct_02080dc0 *l);
extern int func_02064294(UnkStruct_02080dc0_2 *t);
extern void func_02064210(UnkStruct_02080dc0_2 *t, UnkStruct_02080dc0 *l);
extern int func_0203d7c4(int n, UnkStruct_02080dc0 *l);
extern int func_020644cc(int n);
extern int func_0205a240(void *g, u8 x, void *p, int r6, int z, int m);
extern void *func_020641b0(UnkStruct_02080dc0 *l);

void func_02080dc0(void *a, void *b)
{
    UnkStruct_02080dc0 l;
    int r6;
    UnkStruct_02080dc0_2 *t;
    void *p;
    r6 = func_0208150c((unsigned int) a);
    if (func_02003704((void *) r6) == 0) {
        return;
    }
    if (b == 0) {
        return;
    }
    p = func_02099870(b);
    if (func_020951bc(p) == 0) {
        return;
    }
    if (func_02094ffc(p) != 0) {
        return;
    }
    if (func_020807a8(a, p) == 0) {
        return;
    }
    func_020641c8(&l);
    t = &data_021dc7a8.unk_02;
    if (t != 0 && func_02064294(t) != 0) {
        func_02064210(t, &l);
        func_0203d7c4(2, &l);
    }
    func_0205a240(&data_020e1974, (u8) func_020644cc(5), p, r6, 0, -1);
    func_020641b0(&l);
}
