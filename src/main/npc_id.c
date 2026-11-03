/* npc_id: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020037ac @ 0x020037ac, 0x1c bytes, Thumb
 * func_02003790 @ 0x02003790, 0x1c bytes, Thumb
 * func_02003780 @ 0x02003780, 0x10 bytes, Thumb
 * func_02003760 @ 0x02003760, 0x1e bytes, Thumb
 * func_02003750 @ 0x02003750, 0x10 bytes, Thumb
 * func_02003738 @ 0x02003738, 0x16 bytes, Thumb
 * func_02003728 @ 0x02003728, 0x10 bytes, Thumb
 * func_02003704 @ 0x02003704, 0x22 bytes, Thumb
 * func_020036ec @ 0x020036ec, 0x18 bytes, Thumb
 * func_020036e8 @ 0x020036e8, 0x4 bytes, Thumb
 * func_020036d4 @ 0x020036d4, 0x14 bytes, Thumb
 * func_020036c0 @ 0x020036c0, 0x12 bytes, Thumb
 * func_0200368c @ 0x0200368c, 0x34 bytes, Thumb
 * func_0200366c @ 0x0200366c, 0x1e bytes, Thumb
 * func_02003658 @ 0x02003658, 0x14 bytes, Thumb
 * func_0200364c @ 0x0200364c, 0xc bytes, Thumb
 * func_02003648 @ 0x02003648, 0x4 bytes, Thumb
 * func_0200363c @ 0x0200363c, 0xc bytes, Thumb
 * func_02003618 @ 0x02003618, 0x22 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[14];
    unsigned char unk_0E;
    unsigned char unk_0F;
} UnkStruct_020036ec;

struct UnkStruct_0200364c {
    unsigned char pad_00[0x0E];
    unsigned char unk_0E;
};

extern void func_020642bc(void *, const void *);
extern void func_020642a8(void *src, void *dst);
extern void func_020642fc(void *object);
extern void func_020642f8(void *object);
extern void func_020642e0(void *);
extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern int func_02064294(void *ptr);
extern char data_021dc7aa[];
extern void func_020642d0(void *s, void *ptr);
extern void MI_CpuFill8(int a, int b, int c);
extern int func_02064328(int a, void *b, int c, int d);
extern unsigned char data_020d72bc[];
extern int data_020d72a4[];
extern int data_020c7570[];
extern int func_0208249c(int param1, unsigned char param2);

int func_0200363c(unsigned int x);

void func_020037ac(unsigned char *r5, unsigned char *r4)
{
    func_020642bc(r5, r4);
    r5[0xf] = r4[0xf];
    r5[0xe] = r4[0xe];
}

void func_02003790(void *src, void *dst)
{
    unsigned char *s = (unsigned char *) src;
    unsigned char *d = (unsigned char *) dst;

    func_020642a8(src, dst);
    d[0xf] = s[0xf];
    d[0xe] = s[0xe];
}

int func_02003780(int arg)
{
    func_020642fc((void *) arg);
    return arg;
}

void *func_02003760(void *a, void *b)
{
    func_020642fc(a);
    func_020037ac((unsigned char *) a, (unsigned char *) b);
    return a;
}

int func_02003750(int arg)
{
    func_020642f8((void *) arg);
    return arg;
}

void func_02003738(unsigned char *r4)
{
    func_020642e0(r4);
    r4[0xf] = 0xff;
    r4[0xe] = 6;
}

void func_02003728(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0x10);
}

int func_02003704(void *ptr)
{
    int result = 0;
    if (func_02064294(ptr) == 1 && func_0200363c((unsigned char) (((unsigned char *) ptr)[0xf])) == 1) {
        result = 1;
    }
    return result;
}

void func_020036ec(UnkStruct_020036ec *s, unsigned char byte_F, unsigned char byte_E, void *ptr)
{
    s->unk_0F = byte_F;
    s->unk_0E = byte_E;
    if (ptr == 0) {
        ptr = data_021dc7aa;
    }
    func_020642d0(s, ptr);
}

int func_020036e8(unsigned char *p0)
{
    return p0[14];
}

unsigned int func_020036d4(unsigned int x)
{
    unsigned int ret;
    ret = 2;
    if (x < 3) {
        ret = 0;
    } else if (x < 6) {
        ret = 1;
    }
    return ret;
}

unsigned int func_020036c0(unsigned char *argument0)
{
    return func_020036d4((unsigned int) func_020036e8((unsigned char *) argument0));
}

int func_0200368c(int param0, int param1, int param2, int param3)
{
    MI_CpuFill8(param0, 0, param1);
    return func_02064328(param0, data_020d72bc, data_020d72a4[param3], param2);
}

int func_0200366c(int a, int b, int c, int d)
{
    int x = func_020036e8((unsigned char *) a);
    return func_0200368c(b, c, d, x);
}

int func_02003658(unsigned int arg)
{
    int result = 5;

    if (arg < 6) {
        result = data_020c7570[arg];
    }

    return result;
}

int func_0200364c(struct UnkStruct_0200364c *s)
{
    return func_02003658((unsigned char) s->unk_0E);
}

int func_02003648(unsigned char *p0)
{
    return p0[15];
}

int func_0200363c(unsigned int x)
{
    if (x >= 150) {
        return 0;
    } else {
        return 1;
    }
}

int func_02003618(int param1, int param2)
{
    int result;
    int temp;
    int i;
    int j;

    result = 0;
    temp = param1;
    i = param2;

    if (func_02003704((void *) param1) == 1) {
        result = func_0208249c(i, *(unsigned char *) (temp + 0xf));
    }

    return result;
}
