/* scene_object_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201bea4 @ 0x0201bea4, 0xc bytes, Thumb
 * func_0201bdb4 @ 0x0201bdb4, 0xf0 bytes, Thumb
 * func_0201bd48 @ 0x0201bd48, 0x6c bytes, Thumb
 * func_0201bcec @ 0x0201bcec, 0x5c bytes, Thumb
 * func_0201bce8 @ 0x0201bce8, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_0201bd48 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0201bd48;

typedef struct UnkStruct_0201bcec {
    char pad_00[0x4e8];
    unsigned int unk_4E8;
    char pad_4EC[0x563 - 0x4e8 - 4];
    unsigned char unk_563;
    char pad_564[0x62c - 0x563 - 1];
    unsigned char unk_62C;
} UnkStruct_0201bcec;

extern int func_0203f030(unsigned char *);
extern void func_0201c400(unsigned char *, unsigned short *);
extern void func_0201c3f4(unsigned char *, unsigned int);
extern void func_0201a7dc(unsigned char *);
extern void func_0201487c(unsigned char *);
extern void func_0201a74c(unsigned char *);
extern void func_0201b2e0(unsigned char *);
extern void MI_CpuFill8(unsigned char *, int, int);
extern void func_02004490(unsigned char *);
extern void func_02013c14(unsigned char *);
extern void func_02013aac(unsigned char *);
extern void func_0203ed98(unsigned char *);
extern int func_020a7278(void);
extern int func_0201c45c(void *self);
extern void func_0201c0c8(void *self, int a, int b, int c);
extern void func_0201aff4(void *addr, int value);
extern int func_0208239c(void *addr);
extern UnkStruct_0201bd48 *data_020ccf94;
extern void func_0201bf24(UnkStruct_0201bcec *self, int arg);
extern void func_0203f004(UnkStruct_0201bcec *self, int arg);

unsigned char func_0201bea4(const unsigned char *base)
{
    return base[0x561];
}

int func_0201bdb4(unsigned char *param0)
{
    unsigned short local;

    if (func_0203f030(param0) == 0) {
        return 0;
    }

    local = (unsigned short) *(unsigned int *) (param0 + 8);
    func_0201c400(param0, &local);

    *(unsigned int *) (param0 + 0x634) = 0;
    func_0201c3f4(param0, 0xd00);
    func_0201a7dc(param0 + 0x418);
    func_0201487c(param0 + 0x618);
    func_0201a74c(param0 + 0x420);

    param0[0x560] = 0;
    func_0201b2e0(param0 + 0x350);

    param0[0x62c] = 0;
    MI_CpuFill8(param0 + 0x62d, 0, 4);

    func_02004490(param0 + 0x514);
    *(unsigned char **) (param0 + 0x438) = param0 + 0x514;
    func_02013c14(param0 + 0x558);

    param0[0x510] = 1;
    param0[0x511] = 1;
    func_02013aac(param0);

    param0[0x561] = 1;
    param0[0x562] = 1;
    *(unsigned int *) (param0 + 0x628) = 0;
    func_0203ed98(param0);

    return 1;
}

int func_0201bd48(void *self)
{
    if (func_020a7278() != 0) {
        func_0201c0c8(self, 1, data_020ccf94->unk_64, 4);
    }
    if (func_0201c45c(self) == 0) {
        return 0;
    }
    *((int *) ((char *) self + 0xa0)) = -5120;
    *((int *) ((char *) self + 0x9c)) = 0;
    func_0201aff4((char *) self + 0x350, *((short *) ((char *) self + 0x8e)));
    ((unsigned char *) self)[0x447] = (unsigned char) func_0208239c((char *) self + 0xea);
    return 1;
}

void func_0201bcec(UnkStruct_0201bcec *self, int arg2)
{
    if (arg2 == 2) {
        if (func_020a7278() == 0) {
            if ((self->unk_4E8 & 2) == 0) {
                self->unk_4E8 |= 2;
                self->unk_62C = 1;
            }
        }
        if (self->unk_563 == 0) {
            func_0201bf24(self, 1);
        }
    }
    func_0203f004(self, arg2);
}

int func_0201bce8(void *object)
{
    (void) object;
    return 1;
}
