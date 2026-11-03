/* scene_process_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6fd0 @ 0x020b6fd0, 0xa4 bytes, Thumb
 * func_020b6ed4 @ 0x020b6ed4, 0xfc bytes, Thumb
 * func_020b6dcc @ 0x020b6dcc, 0x108 bytes, Thumb
 * func_020b6db4 @ 0x020b6db4, 0x18 bytes, Thumb
 * func_020b6d8c @ 0x020b6d8c, 0x28 bytes, Thumb
 * func_020b6d20 @ 0x020b6d20, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
    int unk_68;
} UnkStruct_020b6ed4;

struct UnkStruct_020b6dcc {
    u8 pad_00[4];
    u8 flag;
};

typedef struct UnkStruct_020b0b00_2 UnkStruct_020b0b00_2;

extern unsigned char data_020e54ac;
extern unsigned char data_020e54b0;
extern int data_021f69d0;
extern void *data_021f693c;
extern void *data_021c8ca0;
extern unsigned char data_021f692c;
extern int data_021f6944;
extern int data_020e55bc[];
extern int data_021f6948;
extern void func_02041a9c(void);
extern int func_020a6ee0(void);
extern void func_020a6ef0(int);
extern void func_0203f070(void);
extern int func_020b5e84(void *);
extern void func_020b7228(void);
extern int func_020b6590(void);
extern void func_020b7e84(void *);
extern void func_020b7130(void);
extern void func_020b71dc(int);
extern void func_020b68f8(void);
extern void func_0208f8fc(void);
extern void func_0200471c(void);
extern UnkStruct_020b6ed4 *data_020ccf94;
extern int func_02073dd4(UnkStruct_020b6ed4 *p, int arg);
extern void func_020961f0(int a, int b);
extern int func_020b6788(void);
extern void func_020738f4(UnkStruct_020b6ed4 *p, int arg);
extern int func_020b65c4(void);
extern void func_020962a4(int a, int b);
extern int func_02096284(int a);
extern void func_02096294(int a);
extern void *data_021fbe94;
extern int func_0203750c(void);
extern int func_020379bc(int, int);
extern void *func_02053e5c(int);
extern void func_02062ae4(int);
extern int func_02072614(void);
extern void func_020726b8(void *);
extern void func_0205cf84(void *);
extern void func_0205d724(void *);
extern void func_0205dd98(void *);
extern void func_0205db10(void *);
extern void func_0205dc58(void *);
extern void func_0205f820(void *);
extern void func_0205d234(void *);
extern void func_0205e8b0(void *);
extern void func_0205f9ac(void *);
extern void func_0205e0f0(void *);
extern void func_0205f6f8(void *);
extern void func_0206094c(void *);
extern void func_020ad4fc(int);
extern int func_020ace54(void);
extern void func_02078da4(void);
extern void func_02082c54(void);
extern void func_020826d0(void);
extern void func_0205c1a4(void *);
extern void func_0209d51c(void);
extern int func_020b5e10(void);
extern void func_020b5e90(void);
extern void func_020ad74c(void);
extern void func_020b0ad4(unsigned int param);
extern int func_020b0abc(UnkStruct_020b0b00_2 **ptr, u8 *cnt, u8 *flag, u64 start);
extern u8 data_021f42dc;
extern u8 data_021f42e4;
extern void func_020b69c8(void *);
extern void func_02091300(void);
extern void func_0208a0ac(void);
extern void func_020b5e88(void *);
extern void func_0203ecac(void);
extern void func_020398b0(void);
extern void func_02035240(void);
extern int data_021d3124;
extern int data_020dd828;

int func_020b6fd0(void)
{
    unsigned char c;
    int callResult;

    func_02041a9c();
    c = data_020e54ac;
    callResult = func_020a6ee0();

    if (c == 0x2e || c == 0xd || c == 0xc || c == 0xe || c == 0x2f) {
        if (callResult != 4) {
            func_020a6ef0(4);
        }
    }

    func_0203f070();
    data_020e54b0 = data_020e54ac;
    data_020e54ac = (unsigned char) func_020b5e84(&data_021f69d0);
    func_020b7228();
    data_021c8ca0 = &data_021f693c;
    func_020b7e84((void *) func_020b6590());
    data_021f692c = 0;
    data_021f6944 = data_020e54ac;
    func_020b7130();
    {
        int v = data_020e55bc[data_020e54ac];
        data_021f6948 = v;
        func_020b71dc(v);
    }
    return 1;
}

int func_020b6ed4(void)
{
    UnkStruct_020b6ed4 *p, *q;
    int r5, r6, r7, i;

    func_020b68f8();
    func_02041a9c();
    func_0208f8fc();
    func_0200471c();

    p = data_020ccf94;

    if (func_02073dd4(p, p->unk_64) != 0) {
        for (r5 = 0; r5 < 4; r5++) {
            func_020961f0(r5, 4);
        }
    } else {
        if (func_020b6788() != 0) {
            func_020738f4(p, 4);
            for (r5 = 0; r5 < 4; r5++) {
                func_020961f0(r5, r5);
            }
        } else {
            func_020738f4(p, 1);
            for (r5 = 0; r5 < 4; r5++) {
                func_020961f0(r5, 4);
            }
        }
    }

    if (func_020b6788() != 0) {
        if (func_020b65c4() == 6) {
            p->unk_68 = 4;
            for (i = 3; i >= 0; i--) {
                func_020962a4(i, i);
            }
        } else if (func_020b65c4() == 7) {
            r6 = p->unk_68;
            r7 = func_02096284(r6);
            r5 = 0;
            for (i = 3; i >= 0; i--) {
                if (i != r6) {
                    if (r5 == r7) {
                        r5++;
                    }
                    func_020962a4(i, r5);
                    r5++;
                }
            }
        }
    } else {
        if (func_020b65c4() == 44) {
            q = data_020ccf94;
            q->unk_64 = 4;
            q->unk_68 = 4;
            for (i = 3; i >= 0; i--) {
                func_02096294(i);
            }
        }
    }
    return 1;
}

int func_020b6dcc(void)
{
    func_020379bc(func_0203750c(), (*(struct UnkStruct_020b6dcc * *) &data_021f6948)->flag == 1);
    func_02053e5c((*(struct UnkStruct_020b6dcc * *) &data_021f6948)->flag == 1);
    func_02062ae4((*(struct UnkStruct_020b6dcc * *) &data_021f6948)->flag == 1);
    func_020726b8((void *) func_02072614());
    func_0205cf84(data_021fbe94);
    func_0205d724(data_021fbe94);
    func_0205dd98(data_021fbe94);
    func_0205db10(data_021fbe94);
    func_0205dc58(data_021fbe94);
    func_0205f820(data_021fbe94);
    func_0205d234(data_021fbe94);
    func_0205e8b0(data_021fbe94);
    func_0205f9ac(data_021fbe94);
    func_0205e0f0(data_021fbe94);
    func_0205f6f8(data_021fbe94);
    func_0206094c(data_021fbe94);
    func_020ad4fc((*(struct UnkStruct_020b6dcc * *) &data_021f6948)->flag == 1);
    func_020ace54();
    func_02078da4();
    func_02082c54();
    func_020826d0();
    func_0205c1a4(data_021fbe94);
    func_0209d51c();
    if (func_020b65c4() == 0x2c || func_020b65c4() == 0x2d) {
        func_020b5e10();
        func_020b5e90();
    }
    func_020ad74c();
    return 1;
}

int func_020b6db4(void)
{
    func_020b0ad4((*(unsigned int *) &data_021f6948));
    return 1;
}

void func_020b6d8c(int unused, u64 start)
{
    func_020b0abc((*(UnkStruct_020b0b00_2 ** *) &data_021f6948), &data_021f42dc, &data_021f42e4, start);
}

int func_020b6d20(void *argument0)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x04000008;

    func_020b69c8((void *) argument0);
    func_02091300();
    *reg = (*reg & ~3) | 2;
    func_0208a0ac();
    data_021d3124 = 0;
    func_020b5e88(&data_021f69d0);
    data_020dd828 = 3;
    func_0203ecac();
    if (func_020b65c4() == 0x2e || func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
        func_020398b0();
    }
    func_02035240();
    return 1;
}
