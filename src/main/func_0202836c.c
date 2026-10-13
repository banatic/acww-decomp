/* func_0202836c @ 0x0202836c, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202836c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_0202836c;

typedef struct UnkStruct_0202836c_2 {
    u8 pad_00[0x100];
    UnkStruct_0202836c *unk_100;
    u8 pad_104[0x20];
    u16 unk_124;
    u8 pad_126[0x36];
    void *unk_15C;
    void *unk_160;
} UnkStruct_0202836c_2;

typedef struct UnkStruct_0202836c_3 {
    s32 a, b;
} UnkStruct_0202836c_3;

extern UnkStruct_0202836c_3 data_020d8f50;
extern UnkStruct_0202836c_3 data_020d8f00;
extern int data_021e5a2c;

extern void *func_020984e8(void);
extern void func_02099640(void);
extern void *func_0202d9c4(UnkStruct_0202836c_2 *);
extern int func_0209bc40(void *);
extern int func_0208150c(void *);
extern void func_0209b4d8(void *, int, int, void *);
extern void func_0209bd5c(void *);
extern void func_0207b57c(int *);
extern int func_0209b4d4(void *);
extern void func_0202d9d0(UnkStruct_0202836c_2 *, int);
extern u16 *func_0209bb70(void *);
extern void *func_02099734(void *);
extern int func_02098eb8(void *);
extern void func_02098f0c(void *, u16 *, int, int);
extern int func_0209a1d0(void);
extern void func_0209b2a8(void *, int);
extern void func_020154b4(UnkStruct_0202836c_2 *, u16 *, int, int, int);
extern void func_0202dbf0(UnkStruct_0202836c_2 *, UnkStruct_0202836c_3);
extern void func_0202db48(UnkStruct_0202836c_2 *, UnkStruct_0202836c_3);

void func_0202836c(UnkStruct_0202836c_2 *p)
{
    void *a1;
    void *q;
    int v;
    int t;
    int t2;

    a1 = func_020984e8();
    func_02099640();
    q = p->unk_100->unk_830;
    v = 2;
    if (p->unk_160 != 0) {
        func_0209b4d8(p->unk_160, func_0209bc40(func_0202d9c4(p)), func_0208150c(q), p->unk_15C);
        func_0209bd5c(func_0202d9c4(p));
        func_0207b57c(&data_021e5a2c);
        func_0202d9d0(p, func_0209b4d4(p->unk_160));
        p->unk_124 = *func_0209bb70(func_0202d9c4(p));
        switch (func_0209bc40(func_0202d9c4(p))) {
            case 0xa:
                t2 = func_02098eb8(func_02099734(a1));
                func_02098f0c(func_02099734(a1), &p->unk_124, t2, v);
                break;
            case 0x13:
                t = func_0209a1d0();
                if (t != 0) {
                    func_0209b2a8(p->unk_160, t);
                }
                v = 0;
                break;
        }
    }
    func_020154b4(p, &p->unk_124, v, 5, 0);
    func_0202dbf0(p, data_020d8f50);
    func_0202db48(p, data_020d8f00);
}
