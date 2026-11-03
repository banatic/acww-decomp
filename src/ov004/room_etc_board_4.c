/* room_etc_board_4: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221b178 @ 0x0221b178, 0x1c bytes, Thumb
 * func_ov004_0221b140 @ 0x0221b140, 0x38 bytes, Thumb
 * func_ov004_0221b104 @ 0x0221b104, 0x3c bytes, Thumb
 * func_ov004_0221b0c4 @ 0x0221b0c4, 0x40 bytes, Thumb
 * func_ov004_0221b060 @ 0x0221b060, 0x64 bytes, Thumb
 */

#include "types.h"

struct SubEC {
    void *ptr;
};

struct UnkStruct_0221b104 {
    void *unk_00;
    char pad_04[0xec - 4];
    struct SubEC subEC;
    char pad_F0[0x138 - 0xf0];
    char sub138;
};

typedef struct UnkStruct_0221b0c4 {
    void *vt0;
    unsigned char pad_04[0xec - 4];
    void *unk_EC;
    unsigned char pad_F0[0x138 - 0xec - 4];
    unsigned char unk_138[1];
} UnkStruct_0221b0c4;

extern int func_020edf70(unsigned int size);
extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_020b7f70(void *);
extern char data_ov004_0225328c[];
extern char data_ov004_022532f4[];
extern int func_020b7f60(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *p);
extern void func_ov004_0221afe8(void);
extern s16 data_ov004_02253238;
extern int data_ov004_022577d0;
extern int func_ov004_0221afb8(void *self);
extern int func_020b65c4(void);
extern void func_0203efb0(void *self, u16 a);
extern int func_ov004_0221ae7c(void *self, int a);

void *func_ov004_0221b140(void *this);

void func_ov004_0221b178(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_020edf70(0x15c)))) {
        func_ov004_0221b140((void *) conditionInput0);
    }
}

void *func_ov004_0221b140(void *this)
{
    func_0203f130(this);
    func_02066a30((char *) this + 0xec);
    *(void **) this = (void *) data_ov004_0225328c;
    *(void **) ((char *) this + 0xec) = (void *) data_ov004_022532f4;
    func_020b7f70((char *) this + 0x138);
    return this;
}

struct UnkStruct_0221b104 *func_ov004_0221b104(struct UnkStruct_0221b104 *this)
{
    this->unk_00 = ((char *) data_ov004_0225328c);
    this->subEC.ptr = ((char *) data_ov004_022532f4);
    func_020b7f60(&this->sub138);
    func_02066994(&this->subEC);
    func_0203f080(this);
    return this;
}

struct UnkStruct_0221b0c4 *func_ov004_0221b0c4(struct UnkStruct_0221b0c4 *this)
{
    this->vt0 = ((char *) data_ov004_0225328c);
    this->unk_EC = ((char *) data_ov004_022532f4);
    func_020b7f60(&this->unk_138);
    func_02066994((void *) (&this->unk_EC));
    func_0203f080(this);
    func_020edf54(this);
    return this;
}

int func_ov004_0221b060(char *self)
{
    func_ov004_0221afe8();
    *(s16 *) (self + 0x156) = data_ov004_02253238;
    *(int *) (self + 0x158) = data_ov004_022577d0;
    if (func_ov004_0221afb8(self)) {
        func_0203efb0(self, (u16) (*(u8 *) (self + 0x154) | (func_020b65c4() << 8)));
        func_ov004_0221ae7c(self, 0);
        return 1;
    }
    return 0;
}
