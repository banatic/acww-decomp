/* field_body_2: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a0c4 @ 0x0208a0c4, 0x4 bytes, Thumb
 * func_0208a0c0 @ 0x0208a0c0, 0x4 bytes, Thumb
 * func_0208a0b8 @ 0x0208a0b8, 0x8 bytes, Thumb
 * func_0208a0b4 @ 0x0208a0b4, 0x4 bytes, Thumb
 * func_0208a0ac @ 0x0208a0ac, 0x8 bytes, Thumb
 * func_0208a0a0 @ 0x0208a0a0, 0xc bytes, Thumb
 * func_0208a088 @ 0x0208a088, 0x18 bytes, Thumb
 * func_0208a07c @ 0x0208a07c, 0xc bytes, Thumb
 * func_0208a078 @ 0x0208a078, 0x2 bytes, Thumb
 * func_0208a038 @ 0x0208a038, 0x40 bytes, Thumb
 * func_0208a020 @ 0x0208a020, 0x18 bytes, Thumb
 * func_0208a000 @ 0x0208a000, 0x20 bytes, Thumb
 * func_02089fe4 @ 0x02089fe4, 0x1c bytes, Thumb
 * func_02089fc8 @ 0x02089fc8, 0x1c bytes, Thumb
 */

typedef struct {
    void *unk_00;
} UnkStruct_0208a088;

struct UnkStruct_0208a000 {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    char pad_0E[14];
    int unk_1C;
    int unk_20;
    char pad_24[16];
    int unk_34;
};

typedef struct UnkStruct_02089fc8 UnkStruct_02089fc8;

struct UnkStruct_02089fc8 {
    unsigned char pad_00[0x38];
    UnkStruct_02089fc8 *unk_38;
};

extern void *func_02089c48(void *);
extern unsigned int data_021d3120;
extern char data_020e201c;
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, int b);
extern int func_020033c4(void *);

void func_0208a0a0(void);
void func_02089fe4(void *r0);

int func_0208a0c4(void)
{
    return 0;
}

int func_0208a0c0(int p0)
{
    return ((int) (p0) + (64));
}

void func_0208a0b8(void *argument0)
{
    func_02089c48((void *) argument0);
}

int func_0208a0b4(int p0)
{
    return ((int) (p0) + (68));
}

void func_0208a0ac(void)
{
    func_0208a0a0();
}

void func_0208a0a0(void)
{
    data_021d3120 = 0;
}

UnkStruct_0208a088 *func_0208a088(UnkStruct_0208a088 *self)
{
    self->unk_00 = (void *) &data_020e201c;
    func_02089fe4(self);
    return self;
}

void func_0208a07c(char **p)
{
    *p = &data_020e201c;
}

void func_0208a078(void) {}

int func_0208a038(unsigned char *p, int q)
{
    if (p[0x3c] != 0) {
        int a = *(int *) (p + 0x10);
        int b = *(int *) (p + 0x18);
        int c = func_020e8ed8(a, b);
        int d = func_020e8b4c(c, (short) (q + 0x8000));
        if (d > 0x2000) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

int func_0208a020(void *arg)
{
    void *tested_value0;
    int result;
    if ((tested_value0 = (void *) (*(int *) ((char *) arg + 0x2c))) != 0) {
        result = func_020033c4(tested_value0);
    } else {
        result = 0;
    }
    return result;
}

void func_0208a000(struct UnkStruct_0208a000 *obj, int a, int b, int c, int d, int e, unsigned char f, int g)
{
    obj->unk_04 = a;
    obj->unk_08 = b;
    obj->unk_1C = c;
    obj->unk_20 = d;
    obj->unk_0C = e;
    obj->unk_0D = f;
    obj->unk_34 = g;
}

void func_02089fe4(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned int zero = 0;

    *(unsigned int *) (p + 0x38) = zero;
    *(unsigned int *) (p + 0x10) = zero;
    *(unsigned int *) (p + 0x14) = zero;
    *(unsigned int *) (p + 0x18) = zero;
    p[0x3c] = (unsigned char) zero;
    *(unsigned int *) (p + 0x2c) = zero;
    *(unsigned int *) (p + 0x28) = zero;
    p[0xe] = (unsigned char) zero;
    p[0xf] = 0xff;
}

void func_02089fc8(UnkStruct_02089fc8 *obj)
{
    func_02089fe4((void *) obj);
    obj->unk_38 = (*(UnkStruct_02089fc8 * *) &data_021d3120);
    (*(UnkStruct_02089fc8 * *) &data_021d3120) = obj;
}
