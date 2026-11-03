/* talk_receiver: 36 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02066954 @ 0x02066954, 0x1e bytes, Thumb
 * func_02066934 @ 0x02066934, 0x1e bytes, Thumb
 * func_02066914 @ 0x02066914, 0x1e bytes, Thumb
 * func_020668d8 @ 0x020668d8, 0x3c bytes, Thumb
 * func_020668d4 @ 0x020668d4, 0x4 bytes, Thumb
 * func_020668cc @ 0x020668cc, 0x6 bytes, Thumb
 * func_020668c8 @ 0x020668c8, 0x4 bytes, Thumb
 * func_020668c0 @ 0x020668c0, 0x8 bytes, Thumb
 * func_020668bc @ 0x020668bc, 0x2 bytes, Thumb
 * func_020668b8 @ 0x020668b8, 0x2 bytes, Thumb
 * func_020668b4 @ 0x020668b4, 0x2 bytes, Thumb
 * func_020668b0 @ 0x020668b0, 0x2 bytes, Thumb
 * func_020668ac @ 0x020668ac, 0x2 bytes, Thumb
 * func_020668a8 @ 0x020668a8, 0x2 bytes, Thumb
 * func_020668a4 @ 0x020668a4, 0x2 bytes, Thumb
 * func_020668a0 @ 0x020668a0, 0x2 bytes, Thumb
 * func_0206689c @ 0x0206689c, 0x2 bytes, Thumb
 * func_02066898 @ 0x02066898, 0x2 bytes, Thumb
 * func_02066894 @ 0x02066894, 0x2 bytes, Thumb
 * func_02066890 @ 0x02066890, 0x2 bytes, Thumb
 * func_0206688c @ 0x0206688c, 0x2 bytes, Thumb
 * func_02066888 @ 0x02066888, 0x2 bytes, Thumb
 * func_02066884 @ 0x02066884, 0x2 bytes, Thumb
 * func_02066880 @ 0x02066880, 0x2 bytes, Thumb
 * func_0206687c @ 0x0206687c, 0x2 bytes, Thumb
 * func_02066878 @ 0x02066878, 0x2 bytes, Thumb
 * func_02066874 @ 0x02066874, 0x2 bytes, Thumb
 * func_02066870 @ 0x02066870, 0x2 bytes, Thumb
 * func_0206686c @ 0x0206686c, 0x2 bytes, Thumb
 * func_02066868 @ 0x02066868, 0x2 bytes, Thumb
 * func_02066864 @ 0x02066864, 0x4 bytes, Thumb
 * func_02066860 @ 0x02066860, 0x4 bytes, Thumb
 * func_0206685c @ 0x0206685c, 0x2 bytes, Thumb
 * func_02066858 @ 0x02066858, 0x2 bytes, Thumb
 * func_02066854 @ 0x02066854, 0x4 bytes, Thumb
 * func_0206684c @ 0x0206684c, 0x6 bytes, Thumb
 */

struct UnkStruct_020668d8;

struct UnkStruct_020668d8_2 {
    unsigned char pad[0x40];
    struct UnkStruct_020668d8 *unk_40;
};

struct UnkStruct_020668d8 {
    int unk_00;
    int unk_04;
    unsigned char pad[0x1a24];
    unsigned char unk_1A2C;
};

typedef struct {
    unsigned char pad_00[68];
    unsigned char unk_44;
} UnkStruct_020668cc;

typedef struct {
    unsigned char pad_00[64];
    unsigned long unk_40;
} UnkStruct_0206684c;

extern int func_020a8be4(void *, int);
extern void *func_020a8bb8(void *, char *);
extern void func_020a8c1c(void *);
extern void func_02067e84(void *ptr);
extern void func_02068b64(void *ptr);
extern int data_020df080;

void func_02066954(void *r0, int r1, int r2)
{
    void *r4 = r0;
    int r5 = r2;

    func_020a8be4((char *) r0 + 0x20, r1);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(char *) ((char *) r4 + 0x44) = 0;
}

void func_02066934(void *r0, int r1, int r2)
{
    void *r4 = r0;
    int r5 = r2;
    func_020a8bb8((char *) r0 + 0x20, (char *) r1);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(unsigned char *) ((char *) r4 + 0x44) = 0;
}

void func_02066914(void *param0, int param1)
{
    void *r4 = param0;
    int r5 = param1;
    func_020a8c1c((char *) r4 + 0x20);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(char *) ((char *) r4 + 0x44) = 1;
}

void func_020668d8(struct UnkStruct_020668d8_2 *self, int argument1, int argument2)
{
    int type;
    int flag;

    type = self->unk_40->unk_04;
    flag = (type == 5);
    func_02066934(self, (int) argument1, (int) argument2);
    if (type != 0 && !flag) {
        func_02067e84(self->unk_40);
        func_02068b64(&self->unk_40->unk_1A2C);
    }
}

int func_020668d4(int p0)
{
    return ((int) (p0) + (32));
}

unsigned char func_020668cc(UnkStruct_020668cc *p)
{
    return p->unk_44;
}

int func_020668c8(int *p0)
{
    return p0[11];
}

int func_020668c0(void)
{
    return (int) &data_020df080;
}

void func_020668bc(void) {}

void func_020668b8(void) {}

void func_020668b4(void) {}

void func_020668b0(void) {}

void func_020668ac(void) {}

void func_020668a8(void) {}

void func_020668a4(void) {}

void func_020668a0(void) {}

void func_0206689c(void) {}

void func_02066898(void) {}

void func_02066894(void) {}

void func_02066890(void) {}

void func_0206688c(void) {}

void func_02066888(void) {}

void func_02066884(void) {}

void func_02066880(void) {}

void func_0206687c(void) {}

void func_02066878(void) {}

void func_02066874(void) {}

void func_02066870(void) {}

void func_0206686c(void) {}

void func_02066868(void) {}

int func_02066864(void)
{
    return 0;
}

int func_02066860(void)
{
    return 5;
}

void func_0206685c(void) {}

void func_02066858(void) {}

void func_02066854(int *p0, int p1)
{
    p0[16] = p1;
}

void func_0206684c(UnkStruct_0206684c *p)
{
    p->unk_40 = 0;
}
