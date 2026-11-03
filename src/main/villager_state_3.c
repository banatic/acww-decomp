/* villager_state_3: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020795c8 @ 0x020795c8, 0x2c bytes, Thumb
 * func_020795a8 @ 0x020795a8, 0x20 bytes, Thumb
 * func_0207956c @ 0x0207956c, 0x3c bytes, Thumb
 * func_02079544 @ 0x02079544, 0x28 bytes, Thumb
 * func_02079540 @ 0x02079540, 0x4 bytes, Thumb
 * func_02079500 @ 0x02079500, 0x3e bytes, Thumb
 * func_020794d8 @ 0x020794d8, 0x28 bytes, Thumb
 * func_020794d4 @ 0x020794d4, 0x4 bytes, Thumb
 * func_020794d0 @ 0x020794d0, 0x4 bytes, Thumb
 * func_020794cc @ 0x020794cc, 0x4 bytes, Thumb
 * func_020794c8 @ 0x020794c8, 0x4 bytes, Thumb
 * func_020794c4 @ 0x020794c4, 0x4 bytes, Thumb
 * func_020794c0 @ 0x020794c0, 0x4 bytes, Thumb
 */

typedef struct {
    char unk_00[0x04];
    void *unk_04;
    char unk_08[0x08];
    void *unk_10;
    char unk_14[0x12];
    unsigned short unk_26;
    void *unk_28;
} UnkStruct_020795c8;

struct GType {
    char pad_00[0x64];
    int val;
};

struct UnkStruct_020794d8 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_020794d8_2 {
    char unk_00;
    unsigned char unk_01;
};

extern void func_0209bd80(void *);
extern int func_0209c53c(void *);
extern void func_02079448(void *);
extern void func_02079444(void *);
extern void func_0209c538(void *);
extern void func_0209bd7c(void *);
extern void func_0209bd5c(void *);
extern void func_0209c52c(void *);
extern void func_02079450(void *);
extern void MI_CpuFill8(void *, int, int);
extern int func_02073dd4(void *, int);
extern struct GType *data_020ccf94;

int func_020794d8(struct UnkStruct_020794d8_2 *param);

UnkStruct_020795c8 *func_020795c8(UnkStruct_020795c8 *obj)
{
    func_0209bd80(&obj->unk_04);
    func_0209c53c(&obj->unk_10);
    obj->unk_26 = 0xfff1;
    func_02079448(&obj->unk_28);
    return obj;
}

void *func_020795a8(void *arg0)
{
    func_02079444((char *) arg0 + 0x28);
    func_0209c538((char *) arg0 + 0x10);
    func_0209bd7c((char *) arg0 + 4);
    return arg0;
}

void func_0207956c(void *r0)
{
    MI_CpuFill8(r0, 0, 0x2c);
    *(unsigned char *) r0 = 0;
    *(unsigned char *) ((char *) r0 + 1) = 3;
    func_0209bd5c((char *) r0 + 4);
    func_0209c52c((char *) r0 + 0x10);
    *(unsigned char *) ((char *) r0 + 0x18) = 5;
    *(unsigned char *) ((char *) r0 + 0x1c) = 0xc;
    *(unsigned int *) ((char *) r0 + 0x20) = 0;
    *(unsigned short *) ((char *) r0 + 0x24) = 0;
    func_02079450(r0);
}

int func_02079544(unsigned char *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->val) != 0 && *param != 7) {
        return 0;
    } else {
        return *param;
    }
}

void func_02079540(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_02079500(unsigned char *p)
{
    switch (*p) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if (func_020794d8((struct UnkStruct_020794d8_2 *) p) == 0) {
                *p = 1;
            } else {
                *p = 0;
            }
            break;
        default:
            break;
    }
}

int func_020794d8(struct UnkStruct_020794d8_2 *param)
{
    if (func_02073dd4((void *) ((*(struct UnkStruct_020794d8 * *) &data_020ccf94)), (*(struct UnkStruct_020794d8 * *) &data_020ccf94)->unk_64) != 0 && param->unk_01 == 0) {
        return 1;
    } else {
        return param->unk_01;
    }
}

void func_020794d4(unsigned char *p0, int p1)
{
    p0[1] = p1;
}

int func_020794d0(int p0)
{
    return ((int) (p0) + (4));
}

int func_020794cc(unsigned char *p0)
{
    return p0[28];
}

void func_020794c8(unsigned char *p0, int p1)
{
    p0[28] = p1;
}

int func_020794c4(unsigned char *p0)
{
    return p0[24];
}

void func_020794c0(unsigned char *p0, int p1)
{
    p0[24] = p1;
}
