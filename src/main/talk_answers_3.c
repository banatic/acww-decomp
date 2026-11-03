/* talk_answers_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ab804 @ 0x020ab804, 0x38 bytes, Thumb
 * func_020ab7e8 @ 0x020ab7e8, 0x1a bytes, Thumb
 * func_020ab79c @ 0x020ab79c, 0x4c bytes, Thumb
 * func_020ab798 @ 0x020ab798, 0x4 bytes, Thumb
 * func_020ab794 @ 0x020ab794, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[7];
    unsigned char unk_08[92];
    unsigned char unk_64[12];
    unsigned char unk_70;
} UnkStruct_020ab804;

extern unsigned char data_021f43ec;
extern void *func_020ab8dc(unsigned char *p);
extern int func_020a82e8(unsigned char *p);
extern void func_020a82e4(void *);
extern void *func_020ab8c4(void *);
extern void func_020a8c1c(void *);
extern void func_020a82b0(void *);
extern void MI_CpuFill8(void *, int, int);

void func_020ab79c(void *arg);

UnkStruct_020ab804 *func_020ab804(UnkStruct_020ab804 *self)
{
    self->unk_00 = data_021f43ec;
    func_020ab8dc(self->unk_08);
    func_020a82e8(self->unk_64);
    self->unk_70 = data_021f43ec;
    func_020ab79c(self);
    return self;
}

void *func_020ab7e8(void *self)
{
    func_020a82e4((char *) self + 0x64);
    func_020ab8c4((char *) self + 0x8);
    return self;
}

void func_020ab79c(void *arg)
{
    unsigned char *p = arg;
    *p = data_021f43ec;
    *(int *) (p + 4) = 0;
    func_020a8c1c(p + 8);
    func_020a82b0(p + 0x64);
    *(p + 0x70) = data_021f43ec;
    MI_CpuFill8(p + 0x71, 0, 0x1a);
    *(p + 0x8b) = 0;
    *(int *) (p + 0x8c) = 0;
}

int func_020ab798(int p0)
{
    return ((int) (p0) + (8));
}

int func_020ab794(int p0)
{
    return ((int) (p0) + (112));
}
