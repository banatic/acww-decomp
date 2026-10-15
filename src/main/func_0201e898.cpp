/* func_0201e898 @ 0x0201e898, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    u32 unk_830;
} TargetStruct;

class PMBase {
  public:
    virtual void v0(int);
};

typedef void (PMBase::*PMFType)(int);

struct UnkStruct_0201e898;

extern "C" void func_0209e474(void *);
extern "C" int func_02020a5c(UnkStruct_0201e898 *, int);
extern "C" void func_0202d8f8(UnkStruct_0201e898 *, void *, void *, u32, int);
extern "C" void func_0202da88(UnkStruct_0201e898 *, const char *);
extern "C" unsigned int func_0208150c(u32);
extern "C" int func_020036e8(unsigned char *);
extern "C" u8 *func_0208222c(unsigned int);
extern "C" int func_020819bc(void *);
extern "C" void func_020819e0(void *);
extern "C" void func_02015fb0(UnkStruct_0201e898 *, int, int, int, int, int);

struct UnkStruct_0201e898 {
    u8 pad_00[0xB0];
    PMFType pmf; // offset 0xB0, 8 bytes
    u8 pad_B8[0x100 - 0xB8];
    void *unk_100; // offset 0x100
    u8 pad_104[0x128 - 0x104];
    s32 unk_128;   // offset 0x128
    void *unk_12C; // offset 0x12C
};

extern unsigned char data_021c2394[];
extern unsigned char data_021c23dc[];
extern unsigned char data_021c23f4[];
extern unsigned char data_021c240c[];
extern unsigned char data_021c2424[];

extern "C" void func_0201e898(UnkStruct_0201e898 *p, int arg1)
{
    u32 val;
    u8 local[8];
    u8 b1, b2, b3;

    val = ((TargetStruct *) p->unk_100)->unk_830;

    *(u32 *) &local[0] = 0;
    *(u32 *) &local[4] = 0;
    func_0209e474(local);

    b3 = local[3];
    b2 = local[2];
    b1 = local[1];

    if (b3 == 0x1f && b2 < 0x17) {
        goto path2;
    } else {
        if (func_02020a5c(p, arg1) == 0) {
            goto path2;
        } else {
            func_0202d8f8(p, &p->unk_12C, &p->unk_128, val, 0);
            return;
        }
    }

path2:
    if (b3 == 0x1f) {
        if (b2 < 0x17) {
            func_0202da88(p, (const char *) data_021c2394);
        } else {
            func_0202da88(p, (const char *) data_021c23dc);
        }
    } else {
        u8 *ptr;

        ptr = func_0208222c((unsigned int) func_020036e8((unsigned char *) func_0208150c(val)));

        if ((unsigned) b2 < (unsigned) ptr[2] || ((unsigned) b2 == (unsigned) ptr[2] && (unsigned) b1 < (unsigned) ptr[3])) {
            func_0202da88(p, (const char *) data_021c23f4);
        } else {
            if (p->unk_12C == 0 || func_020819bc(p->unk_12C) == 0) {
                func_0202da88(p, (const char *) data_021c240c);
            } else {
                func_0202da88(p, (const char *) data_021c2424);
            }
        }

        func_02015fb0(p, local[5] + 0x7d0, 0, 4, 0, 0);
    }

    if (p->pmf != 0) {
        (((PMBase *) p)->*(p->pmf))(arg1);
    }

    func_0202d8f8(p, &p->unk_12C, &p->unk_128, val, 0);

    if (p->unk_12C != 0) {
        func_020819e0(p->unk_12C);
    }
}
