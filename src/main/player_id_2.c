/* player_id_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209529c @ 0x0209529c, 0x10 bytes, Thumb
 * func_0209527c @ 0x0209527c, 0x1e bytes, Thumb
 * func_0209526c @ 0x0209526c, 0x10 bytes, Thumb
 * func_0209525c @ 0x0209525c, 0x10 bytes, Thumb
 * func_02095238 @ 0x02095238, 0x22 bytes, Thumb
 * func_02095208 @ 0x02095208, 0x30 bytes, Thumb
 * func_020951dc @ 0x020951dc, 0x2c bytes, Thumb
 * func_020951bc @ 0x020951bc, 0x1e bytes, Thumb
 * func_0209518c @ 0x0209518c, 0x30 bytes, Thumb
 * func_02095158 @ 0x02095158, 0x34 bytes, Thumb
 * func_02095128 @ 0x02095128, 0x2e bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[14];
    unsigned short unk_0E;
} UnkStruct_020951bc;

struct UnkStruct_0209518c {
    unsigned char pad_00[0x0e];
    unsigned short unk_0E;
    unsigned char data[0x0c];
    signed char unk_1C;
};

typedef struct {
    unsigned char pad_00[0x0E];
    unsigned short unk_0E;
    unsigned char data[0x0C];
    unsigned char unk_1C;
} UnkStruct_02095158;

extern void func_020642fc(void *object);
extern void func_020642f8(void *object);
extern void MI_CpuCopy8(int a, int b, int c);
extern void func_020642e0(void *);
extern void MI_CpuFill8(void *, int, int);
extern void func_020642bc(void *a, void *b);
extern void func_020642a8(void *src, void *dst);
extern int func_02064294(UnkStruct_020951bc *p);
extern int __arm memcmp(const void *a, const void *b, unsigned int len);
extern void func_020642d0(void *self, void *ptr);
extern char data_021dc7aa;

void func_02095208(char *a, char *b);

void *func_0209529c(void *r0)
{
    func_020642fc(r0);
    return r0;
}

int func_0209527c(int a, int b)
{
    func_020642fc((void *) a);
    func_02095208((char *) a, (char *) b);
    return a;
}

int func_0209526c(int arg)
{
    func_020642f8((void *) arg);
    return arg;
}

void func_0209525c(int a, int b)
{
    MI_CpuCopy8(b, a, 0x1e);
}

void func_02095238(void *arg0)
{
    MI_CpuFill8((char *) arg0 + 0x10, 0, 0xc);
    *(unsigned short *) ((char *) arg0 + 0xe) = 0;
    *(unsigned char *) ((char *) arg0 + 0x1c) = 2;
    func_020642e0(arg0);
}

void func_02095208(char *a, char *b)
{
    MI_CpuCopy8((int) (b + 0x10), (int) (a + 0x10), 0xc);
    *(unsigned short *) (a + 0xe) = *(unsigned short *) (b + 0xe);
    *(signed char *) (a + 0x1c) = *(signed char *) (b + 0x1c);
    func_020642bc(a, b);
}

void func_020951dc(void *src, void *dst)
{
    MI_CpuCopy8((int) ((char *) src + 0x10), (int) ((char *) dst + 0x10), 0xc);
    *(unsigned short *) ((char *) dst + 0xe) = *(unsigned short *) ((char *) src + 0xe);
    *(char *) ((char *) dst + 0x1c) = *(signed char *) ((char *) src + 0x1c);
    func_020642a8(src, dst);
}

int func_020951bc(UnkStruct_020951bc *p)
{
    if (func_02064294(p) == 1 && p->unk_0E != 0) {
        return 1;
    }
    return 0;
}

int func_0209518c(const struct UnkStruct_0209518c *a, const struct UnkStruct_0209518c *b)
{
    return (a->unk_0E == b->unk_0E) && (a->unk_1C == b->unk_1C) && (memcmp(a->data, b->data, 0xc) == 0);
}

void func_02095158(UnkStruct_02095158 *self, void *src, unsigned short val1, unsigned char val2, void *ptr)
{
    MI_CpuCopy8((int) src, (int) self->data, 12);
    self->unk_0E = val1;
    self->unk_1C = val2;
    if (ptr == 0) {
        ptr = &data_021dc7aa;
    }
    func_020642d0(self, ptr);
}

int func_02095128(unsigned short value, unsigned short *array, int length)
{
    int found;
    int i;

    found = 0;
    if (length != 0 && array != 0) {
        for (i = 0; i < length; array++, i++) {
            if (value == *array) {
                found = 1;
                break;
            }
        }
    }
    return found;
}
