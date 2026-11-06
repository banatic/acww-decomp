/* session_villager_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020785a4 @ 0x020785a4, 0x36 bytes, Thumb
 * func_02078540 @ 0x02078540, 0x64 bytes, Thumb
 * func_020784f8 @ 0x020784f8, 0x48 bytes, Thumb
 * func_020784b0 @ 0x020784b0, 0x48 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[2];
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_020785a4;

extern unsigned short func_02077898(const UnkStruct_020785a4 *in);
extern int func_02073d90(void *g);
extern void func_020785dc(int *outBuf, void *p0, void *p1, void *p2, void *p3, u8 flag);
extern void func_02073820(void *g);
extern void func_020737f0(void *g, int *buf, int n);
extern void func_02073770(void *g, int a, int n);
extern int func_0207f294(int a);
extern int func_0207cf74(int x);
extern unsigned char data_020ccf94[];

void func_020785a4(int *out0, unsigned char *out1, unsigned short *out2, int *out3, unsigned char *out4,
                   const UnkStruct_020785a4 *in)
{
    *out0 = (in->unk_02 >> 4) & 0xF;
    *out3 = in->unk_02 & 7;
    *out4 = (in->unk_02 >> 3) & 1;
    *out1 = in->unk_03;
    *out2 = func_02077898(in);
}

void func_02078540(void *p0, void *p1, void *p2, void *p3, u8 flag)
{
    if (func_02073d90((*(void **) data_020ccf94))) {
        int local;
        void *g;

        func_020785dc(&local, p0, p1, p2, p3, (u8) (flag != 0));
        g = (*(void **) data_020ccf94);
        func_02073820(g);
        func_020737f0(g, &local, 4);
        func_02073770(g, 0x3d, 4);
    }
}

void func_020784f8(int a, int b, int c, int d, unsigned char e)
{
    if (func_02073d90(*(void **) data_020ccf94) == 0) {
        return;
    }
    a = func_0207f294(a);
    if (func_0207cf74(a) == 0) {
        return;
    }
    func_02078540((void *) a, (void *) b, (void *) c, (void *) d, (unsigned char) e);
}

void func_020784b0(unsigned int param1, unsigned int param2)
{
    extern void func_02078460(unsigned int *, unsigned int, unsigned int);

    unsigned int local;
    unsigned int *ptr;

    if (func_02073d90((void *) ((*(unsigned int *) data_020ccf94)))) {
        func_02078460(&local, param1, param2);
        ptr = (unsigned int *) (*(unsigned int *) data_020ccf94);
        func_02073820((void *) ((unsigned int) ptr));
        func_020737f0((void *) ((unsigned int) ptr), (int *) (&local), 3);
        func_02073770((void *) ((unsigned int) ptr), 0x3f, 4);
    }
}
