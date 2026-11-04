/* sound_scene_6: 9 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f45c4 @ 0x020f45c4, 0x84 bytes, ARM
 * func_020f458c @ 0x020f458c, 0x38 bytes, ARM
 * func_020f454c @ 0x020f454c, 0x40 bytes, ARM
 * func_020f4514 @ 0x020f4514, 0x38 bytes, ARM
 * func_020f4510 @ 0x020f4510, 0x4 bytes, ARM
 * func_020f450c @ 0x020f450c, 0x4 bytes, ARM
 * func_020f44f8 @ 0x020f44f8, 0x14 bytes, ARM
 * func_020f44b8 @ 0x020f44b8, 0x40 bytes, ARM
 * func_020f43f8 @ 0x020f43f8, 0xc0 bytes, ARM
 */

#include "types.h"

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
    struct UnkStruct_020f45c4 *unk_30;
    char pad_34[0x4d - 0x34];
    u8 unk_4D;
} UnkStruct_020f45c4_2;

typedef struct UnkStruct_020f45c4 {
    char pad_00[0x3c];
    u8 unk_3C;
} UnkStruct_020f45c4;

typedef struct {
    void *vtable;
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
} UnkStruct_020f45c4_3;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} Global_021fd1bc;

typedef struct Vtbl Vtbl;

typedef struct UnkStruct_020f454c {
    const Vtbl *vtable;
} UnkStruct_020f454c;

typedef struct Global {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} Global;

struct Object {
    void *vt;
};

struct State {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
};

extern void func_020f65bc(UnkStruct_020f45c4 *ptr, int param);
extern void func_020f11d0(UnkStruct_020f45c4_2 *global, int a, int b);
extern void NNS_SndPlayerSetPlayerVolume(int a, int b);
extern void func_020f5a3c(char value);
extern unsigned char data_0213efb4[];
extern void NNS_SndHeapLoadState(int, int);
extern void func_020edb3c(UnkStruct_020f454c *self);
extern void func_020f0fb0(void *arg, int value);
extern unsigned char data_021fd1bc[];
extern void func_020f6700(int);
extern void NNS_SndPlayerStopSeqByPlayerNo(int playerNo, int handle);

void func_020f43f8(int unused, int handle);

UnkStruct_020f45c4_3 *func_020f45c4(UnkStruct_020f45c4_3 *this)
{
    UnkStruct_020f45c4 *p;
    this->vtable = (void *) data_0213efb4;
    (*(UnkStruct_020f45c4_2 *) data_021fd1bc).unk_2C = this;
    (*(UnkStruct_020f45c4_2 *) data_021fd1bc).unk_4D = 0;
    (*(UnkStruct_020f45c4_2 *) data_021fd1bc).unk_30->unk_3C = 0;
    if ((*(UnkStruct_020f45c4_2 *) data_021fd1bc).unk_30 != 0) {
        func_020f65bc((*(UnkStruct_020f45c4_2 *) data_021fd1bc).unk_30, 0xd2);
    }
    func_020f11d0(((UnkStruct_020f45c4_2 *) data_021fd1bc), 0x7f, 0x7f);
    NNS_SndPlayerSetPlayerVolume(0xf, 0x64);
    this->unk_04 = -1;
    this->unk_05 = 0;
    this->unk_06 = 0;
    func_020f5a3c(0);
    return this;
}

void *func_020f458c(void *p)
{
    int x;
    *(void **) p = ((char *) data_0213efb4);
    x = (*(Global_021fd1bc *) data_021fd1bc).unk_28;
    (*(Global_021fd1bc *) data_021fd1bc).unk_2C = 0;
    NNS_SndHeapLoadState(x, 0);
    return p;
}

UnkStruct_020f454c *func_020f454c(UnkStruct_020f454c *self)
{
    int tmp;

    self->vtable = ((const Vtbl *) data_0213efb4);
    tmp = (*(Global *) data_021fd1bc).unk_28;
    (*(Global *) data_021fd1bc).unk_2C = 0;
    NNS_SndHeapLoadState(tmp, 0);
    func_020edb3c(self);

    return self;
}

void *func_020f4514(void *obj)
{
    struct Object *self = (struct Object *) obj;
    int arg;

    self->vt = (void *) ((int *) data_0213efb4);
    arg = (*(struct State *) data_021fd1bc).unk_28;
    (*(struct State *) data_021fd1bc).unk_2C = 0;
    NNS_SndHeapLoadState(arg, 0);
    return self;
}

void func_020f4510(void *receiver) {}

void func_020f450c(void) {}

void func_020f44f8(void *receiver, int value)
{
    func_020f0fb0(((char *) data_021fd1bc), value);
}

int func_020f44b8(void *arg)
{
    int val;
    val = *(int *) (data_021fd1bc + 0x30);
    func_020f6700(val);
    data_021fd1bc[0x4d] = 1;
    func_020f43f8((int) arg, 15);
    ((char *) arg)[5] = 1;
    return 1;
}

void func_020f43f8(int unused, int handle)
{
    NNS_SndPlayerStopSeqByPlayerNo(0xb, handle);
    NNS_SndPlayerStopSeqByPlayerNo(2, handle);
    NNS_SndPlayerStopSeqByPlayerNo(4, handle);
    NNS_SndPlayerStopSeqByPlayerNo(5, handle);
    NNS_SndPlayerStopSeqByPlayerNo(6, handle);
    NNS_SndPlayerStopSeqByPlayerNo(7, handle);
    NNS_SndPlayerStopSeqByPlayerNo(8, handle);
    NNS_SndPlayerStopSeqByPlayerNo(9, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xa, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xc, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xf, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x10, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x11, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x12, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x13, handle);
}
