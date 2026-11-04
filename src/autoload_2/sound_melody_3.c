/* sound_melody_3: 10 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f65fc @ 0x020f65fc, 0x10 bytes, ARM
 * func_020f65d0 @ 0x020f65d0, 0x2c bytes, ARM
 * func_020f65c8 @ 0x020f65c8, 0x8 bytes, ARM
 * func_020f65bc @ 0x020f65bc, 0xc bytes, ARM
 * func_020f6580 @ 0x020f6580, 0x3c bytes, ARM
 * func_020f6564 @ 0x020f6564, 0x1c bytes, ARM
 * func_020f6560 @ 0x020f6560, 0x4 bytes, ARM
 * func_020f655c @ 0x020f655c, 0x4 bytes, ARM
 * func_020f6508 @ 0x020f6508, 0x54 bytes, ARM
 * func_020f64c8 @ 0x020f64c8, 0x40 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[56];
    unsigned char unk_38;
} UnkStruct_020f65c8;

struct UnkStruct_020f6580 {
    char pad_00[0x28];
    int x;
};

struct Global_021fd1bc {
    char pad_00[0x28];
    int unk_28;
};

typedef struct {
    char unk_00[6];
    signed char unk_06;
    signed char unk_07;
    signed char unk_08;
    signed char unk_09;
    signed char unk_0A;
} UnkStruct_020f6508;

typedef struct {
    unsigned int flags;
    char pad_04[6];
    char unk_0A;
} UnkStruct_020f64c8;

extern void func_020f6f88(void *ptr, int argument1);
extern int func_020f69cc(void *);
extern void func_020f6f80(void *argument0, unsigned short argument1);
extern void NNS_SndHeapLoadState(int, int);
extern int func_0210e198(int, int);
extern unsigned char data_021fd1bc[];
extern int func_0210e1d0(int a, int b);
extern int func_020f6948(int param);
extern void func_020eed48(void *res);
extern int data_021fd268;
extern int func_020eed18(UnkStruct_020f64c8 *obj, int val);
extern void NNS_SndHandleReleaseSeq(UnkStruct_020f64c8 *obj);

void func_020f65fc(void *ptr, int argument1)
{
    func_020f6f88((char *) ptr + 0x14, argument1);
}

int func_020f65d0(void *r0)
{
    int r1;
    r1 = (func_020f69cc(r0) >= 0) ? 1 : 0;
    *(unsigned char *) ((char *) r0 + 0x38) = r1;
    return func_020f69cc((char *) r0 + 0x14);
}

unsigned char func_020f65c8(UnkStruct_020f65c8 *p)
{
    return p->unk_38;
}

void func_020f65bc(void *argument0, unsigned short argument1)
{
    func_020f6f80(argument0, argument1);
}

void func_020f6580(int a, int b)
{
    struct UnkStruct_020f6580 *p = (struct UnkStruct_020f6580 *) data_021fd1bc;
    int v = p->x;
    NNS_SndHeapLoadState(v, 0);
    func_0210e198(b, v);
}

int func_020f6564(int a, int b)
{
    return func_0210e1d0(b, (*(struct Global_021fd1bc *) data_021fd1bc).unk_28);
}

void func_020f6560(void *self) {}

void func_020f655c(void *self) {}

void func_020f6508(UnkStruct_020f6508 *self)
{
    data_021fd268 = func_020f6948(((int *) data_021fd1bc)[12]);
    func_020eed48((void *) self);
    self->unk_0A = 0;
    self->unk_06 = -1;
    self->unk_07 = 0;
    self->unk_09 = -1;
    self->unk_08 = self->unk_09;
}

void func_020f64c8(UnkStruct_020f64c8 *obj)
{
    int b = 0;
    obj->unk_0A = 0;
    if (obj->flags) {
        b = 1;
    }
    if (b != 0) {
        func_020eed18(obj, 0);
    }
    NNS_SndHandleReleaseSeq(obj);
}
