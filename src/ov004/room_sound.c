/* room_sound: 15 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223d020 @ 0x0223d020, 0x6 bytes, Thumb
 * func_ov004_0223d010 @ 0x0223d010, 0x10 bytes, Thumb
 * func_ov004_0223cfec @ 0x0223cfec, 0x24 bytes, Thumb
 * func_ov004_0223cfd4 @ 0x0223cfd4, 0x18 bytes, Thumb
 * func_ov004_0223cfcc @ 0x0223cfcc, 0x8 bytes, Thumb
 * func_ov004_0223cfc8 @ 0x0223cfc8, 0x2 bytes, Thumb
 * func_ov004_0223cfc4 @ 0x0223cfc4, 0x4 bytes, Thumb
 * func_ov004_0223cfbc @ 0x0223cfbc, 0x6 bytes, Thumb
 * func_ov004_0223cfb8 @ 0x0223cfb8, 0x2 bytes, Thumb
 * func_ov004_0223cf80 @ 0x0223cf80, 0x38 bytes, Thumb
 * func_ov004_0223cf68 @ 0x0223cf68, 0x18 bytes, Thumb
 * func_ov004_0223cf54 @ 0x0223cf54, 0x14 bytes, Thumb
 * func_ov004_0223cf40 @ 0x0223cf40, 0x14 bytes, Thumb
 * func_ov004_0223cf2c @ 0x0223cf2c, 0x14 bytes, Thumb
 * func_ov004_0223cf18 @ 0x0223cf18, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[16];
    unsigned char unk_10;
} UnkStruct_0223d020;

typedef struct {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short linkOffset;
    void *handle;
} SoundResources;

typedef struct {
    SoundResources resources;
    unsigned char initialized;
} SoundOwner;

typedef struct {
    unsigned char pad_00[16];
    unsigned char unk_10;
} UnkStruct_0223cfc4;

typedef struct {
    unsigned char pad_00[28];
    unsigned char unk_1C;
} UnkStruct_0223cfbc;

extern void *func_020f4f64(int);
extern int func_0200431c(void);
extern void func_02004414(char *self);
extern void func_0200440c(int);
extern void *func_ov004_0223d028(void);
extern void func_02004404(void *, void *);
extern void func_02004328(void *);
extern void func_020043c4(void *, int, int);
extern void func_02004384(void *, int, int);
extern void func_02004330(void *, int);
extern void func_02004320(void *object, short value);

unsigned char func_ov004_0223cfc4(UnkStruct_0223cfc4 *p);

void func_ov004_0223d020(UnkStruct_0223d020 *p)
{
    p->unk_10 = 0;
}

int func_ov004_0223d010(int arg)
{
    func_020f4f64(arg);
    return arg;
}

void func_ov004_0223cfec(char *self)
{
    if ((int) func_ov004_0223cfc4((UnkStruct_0223cfc4 *) self) == 0 && func_0200431c() != 0) {
        func_02004414(self);
        *(u8 *) (self + 0x10) = 1;
    }
}

void func_ov004_0223cfd4(int r0)
{
    int r4;
    int result;

    r4 = r0;
    result = (int) func_ov004_0223cfc4((UnkStruct_0223cfc4 *) ((void *) r0));
    if (result != 0) {
        func_0200440c(r4);
    }
}

void func_ov004_0223cfcc(void *p)
{
    func_ov004_0223cfc4((UnkStruct_0223cfc4 *) p);
}

void *func_ov004_0223cfc8(void *object)
{
    SoundOwner *self = object;
    return &self->resources;
}

unsigned char func_ov004_0223cfc4(UnkStruct_0223cfc4 *p)
{
    return p->unk_10;
}

void func_ov004_0223cfbc(UnkStruct_0223cfbc *p)
{
    p->unk_1C = 0;
}

void func_ov004_0223cfb8(void *object) {}

void func_ov004_0223cf80(char *self)
{
    void *p;
    if (*(u8 *) (self + 0x1c) == 0) {
        p = func_ov004_0223d028();
        if (p != 0) {
            if ((int) func_ov004_0223cfc4((UnkStruct_0223cfc4 *) p) != 0) {
                func_02004404(self, func_ov004_0223cfc8(p));
                *(u8 *) (self + 0x1c) = 1;
            }
        }
    }
}

void func_ov004_0223cf68(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004328(self);
        *(u8 *) (self + 0x1c) = 0x0;
    }
}

void func_ov004_0223cf54(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_020043c4(self, a1, a2);
    }
}

void func_ov004_0223cf40(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004384(self, a1, a2);
    }
}

void func_ov004_0223cf2c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1c) != 0x0) {
        func_02004330(self, a1);
    }
}

void func_ov004_0223cf18(char *self, short value)
{
    if (*(u8 *) (self + 0x1c) != 0) {
        func_02004320(self, value);
    }
}
