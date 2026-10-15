/* func_02090fd0 @ 0x02090fd0, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02090fd0 {
    u8 pad_00[0x30];
    int unk_30;
} UnkStruct_02090fd0;

typedef struct UnkStruct_02090fd0_2 {
    u8 pad_00[0x50];
    UnkStruct_02090fd0 *unk_50;
    int unk_54;
    u8 unk_58[0x35c - 0x58];
    u8 unk_35C[0x181c - 0x35c];
    u8 unk_181C[4];
} UnkStruct_02090fd0_2;

extern UnkStruct_02090fd0_2 *data_021d52c4;
extern void *data_021d52cc;
extern void *data_021d52d4;
extern void *data_021d52d0;

extern void *func_020e98b4(int n);
extern void *NNS_FndCreateFrmHeapEx(void *h, int n, int z);
extern UnkStruct_02090fd0 *func_020fa9f4(void *fn, int a, int b, int c, int d, int e);
extern void func_020fa820(UnkStruct_02090fd0 *q, void *h);
extern void func_020fa564(UnkStruct_02090fd0 *q, void *r);
extern void func_020e9898(void *h);
extern void NNS_FndDestroyFrmHeap(void *h);
extern void MI_CpuFill8(void *dst, int c, int n);
extern void *func_02091130(void);
extern int func_0209110c(UnkStruct_02090fd0_2 *p);
extern void *func_020910e4(UnkStruct_02090fd0_2 *p, void *h);
extern void func_02090968(void *x);
extern void func_02090858(void *x);
extern void func_0209033c(void *x);
extern void *func_02091140(int);

int func_02090fd0(UnkStruct_02090fd0_2 *p)
{
    int ok;
    void *h;
    void *r;

    ok = 0;
    data_021d52c4 = p;
    p->unk_50 = 0;
    data_021d52cc = 0;
    p->unk_54 = 0;
    data_021d52d4 = 0;
    data_021d52d0 = func_020e98b4(0xc000);
    if (data_021d52d0 != 0) {
        data_021d52cc = NNS_FndCreateFrmHeapEx(data_021d52d0, 0xc000, 0);
        p->unk_50 = func_020fa9f4((void *) func_02091140, 0x20, 0x64, 0x14, 0x15, 0x32);
        p->unk_50->unk_30 = 0x8800;
        if (p->unk_50 != 0) {
            asm { add r0, p, #0 }
            h = func_02091130();
            if (h != 0) {
                func_020fa820(p->unk_50, h);
                if (func_0209110c(p)) {
                    r = func_020910e4(p, h);
                    if (r != 0) {
                        func_020fa564(p->unk_50, r);
                        ok = 1;
                    }
                }
                func_020e9898(h);
            }
        }
    }
    if (ok == 0) {
        if (data_021d52cc != 0) {
            NNS_FndDestroyFrmHeap(data_021d52cc);
            data_021d52cc = 0;
        }
        if (data_021d52d0 != 0) {
            func_02090968(p->unk_58);
            func_020e9898(data_021d52d0);
            data_021d52d0 = 0;
        }
    } else {
        MI_CpuFill8(p->unk_35C, 0, 0x14c0);
        func_02090858(p->unk_35C);
        func_0209033c(p->unk_181C);
    }
    return ok;
}
