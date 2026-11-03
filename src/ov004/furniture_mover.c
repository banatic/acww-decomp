/* furniture_mover: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223b004 @ 0x0223b004, 0x54 bytes, Thumb
 * func_ov004_0223afd4 @ 0x0223afd4, 0x30 bytes, Thumb
 * func_ov004_0223afb4 @ 0x0223afb4, 0x1e bytes, Thumb
 * func_ov004_0223af18 @ 0x0223af18, 0x9c bytes, Thumb
 * func_ov004_0223af08 @ 0x0223af08, 0xe bytes, Thumb
 * func_ov004_0223ae0c @ 0x0223ae0c, 0xfc bytes, Thumb
 * func_ov004_0223ae00 @ 0x0223ae00, 0xa bytes, Thumb
 * func_ov004_0223adfc @ 0x0223adfc, 0x4 bytes, Thumb
 * func_ov004_0223adf8 @ 0x0223adf8, 0x4 bytes, Thumb
 * func_ov004_0223adf4 @ 0x0223adf4, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    long x, y, z;
} UnkStruct_0223b004;

typedef struct {
    unsigned char pad_00[24];
    unsigned long unk_18;
} UnkStruct_0223adfc;

typedef struct {
    unsigned char pad_00[28];
    unsigned long unk_1C;
} UnkStruct_0223adf8;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0223adf4;

extern void func_02055124(void *);
extern void func_02055e64(void *);
extern int func_02056f94(void *);
extern void *func_020ea0e0(int, void *);
extern void *data_021fbe94;
extern void func_020e9fc8(void *argument0);
extern void *func_02064b2c(void *, void *, int, int);
extern int NNS_FndMountArchive(void *, void *, void *);
extern void *NNS_FndGetArchiveFileByName(void *);
extern void *NNS_G3dGetJntAnmSet(void *);
extern void *func_02107b44(void *, int);
extern int func_0210285c(void *);
extern char data_ov004_02256114;
extern char data_ov004_02256128;
extern char data_ov004_0225612c;
extern char data_ov004_02256148;
extern char data_ov004_02256164;
extern int func_0204bc64(u16 *);
extern int func_02064328(char *, void *, ...);
extern char *func_02107828(void *);
extern int func_02055f40(void *, void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void func_02055dc8(void *, int, int);
extern void func_ov004_0223b1b8(void *);
extern char data_ov004_022560fc;
extern char data_ov004_02256110;
extern void *data_ov004_02255f70;

unsigned long func_ov004_0223adfc(UnkStruct_0223adfc *p);

int func_ov004_0223b004(char *self, unsigned char *flag, UnkStruct_0223b004 *out)
{
    if (*(unsigned char *) self != 0 && *flag != 0) {
        func_02055124(self + 0x2c);
        func_02055e64(self + 0x2c);
        out->x = *(long *) (self + 4);
        out->y = *(long *) (self + 8);
        out->z = *(long *) (self + 0xc);
        if (func_02056f94(self + 0xc8) != 0) {
            *flag = 0;
            *(unsigned char *) self = *flag;
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_ov004_0223afd4(char *self)
{
    if (*(void **) (self + 0x10) == 0) {
        *(void **) (self + 0x10) = func_020ea0e0(0x2800, data_021fbe94);
        if (*(void **) (self + 0x10) != 0) {
            return 1;
        }
    }
    return 0;
}

int func_ov004_0223afb4(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x10) != 0x0) {
        func_020e9fc8((void *) (*(int *) (self + 0x10)));
        *(void **) (self + 0x10) = 0x0;
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0223af18(char *self)
{
    char buf[0x68];
    void *p;
    if (*(void **) (self + 0x14) == 0) {
        *(void **) (self + 0x14) = func_02064b2c(&data_ov004_02256114, *(void **) (self + 0x10), 4, 0);
        if (*(void **) (self + 0x14) == 0) {
            return 0;
        }
        if (NNS_FndMountArchive(buf, &data_ov004_02256128, *(void **) (self + 0x14)) != 0) {
            p = NNS_FndGetArchiveFileByName(&data_ov004_0225612c);
            if (p != 0) {
                *(void **) (self + 0x18) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            p = NNS_FndGetArchiveFileByName(&data_ov004_02256148);
            if (p != 0) {
                *(void **) (self + 0x1c) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            p = NNS_FndGetArchiveFileByName(&data_ov004_02256164);
            if (p != 0) {
                *(void **) (self + 0x20) = func_02107b44(NNS_G3dGetJntAnmSet(p), 0);
            }
            func_0210285c(buf);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0223af08(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x14) = 0x0;
    *(void **) (self + 0x18) = 0x0;
    *(void **) (self + 0x1c) = 0x0;
    *(void **) (self + 0x20) = 0x0;
    return 0x1;
}

int func_ov004_0223ae0c(char *self)
{
    u16 item;
    char name[0x2a];
    char buf[0x68];
    int ok;
    if (*(void **) (self + 0x10) == 0) {
        return 0;
    }
    if (*(void **) (self + 0x24) != 0) {
        return 0;
    }
    if (*(void **) (self + 0x28) != 0) {
        return 0;
    }
    item = 0x3984;
    {
        int id = func_0204bc64(&item);
        func_02064328(name, &data_ov004_022560fc, id >> 8, (id & 0xff) >> 4, id);
    }
    *(void **) (self + 0x24) = func_02064b2c((void *) name, *(void **) (self + 0x10), 4, 0);
    if (*(void **) (self + 0x24) != 0 && NNS_FndMountArchive(buf, &data_ov004_02256110, *(void **) (self + 0x24)) != 0) {
        char *res;
        ok = 0;
        res = func_02107828((char *) NNS_FndGetArchiveFileByName(data_ov004_02255f70));
        *(char **) (self + 0x28) = res + *(int *) (res + *(u16 *) (res + 0xe) + 0xc);
        if (func_02055f40(self + 0x2c, *(void **) (self + 0x28), ok) != 0 &&
            func_02055140(self + 0x2c, *(void **) (self + 0x10)) != 0) {
            int a = (int) func_ov004_0223adfc((UnkStruct_0223adfc *) self);
            func_02055060(self + 0x2c, a, 1, 0x1000, ok, ok);
            func_02055050(self + 0x2c);
            func_02055dc8(self + 0x2c, (int) func_ov004_0223b1b8, (int) self);
            ok = 1;
        }
        func_0210285c(buf);
        return ok;
    }
    return 0;
}

int func_ov004_0223ae00(char *self)
{
    *(int *) (self + 0x24) = 0;
    *(int *) (self + 0x28) = 0;
    return 1;
}

unsigned long func_ov004_0223adfc(UnkStruct_0223adfc *p)
{
    return p->unk_18;
}

unsigned long func_ov004_0223adf8(UnkStruct_0223adf8 *p)
{
    return p->unk_1C;
}

unsigned long func_ov004_0223adf4(UnkStruct_0223adf4 *p)
{
    return p->unk_20;
}
