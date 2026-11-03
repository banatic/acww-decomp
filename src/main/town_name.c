/* town_name: 24 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020642fc @ 0x020642fc, 0x2 bytes, Thumb
 * func_020642f8 @ 0x020642f8, 0x2 bytes, Thumb
 * func_020642e0 @ 0x020642e0, 0x18 bytes, Thumb
 * func_020642d0 @ 0x020642d0, 0x10 bytes, Thumb
 * func_020642bc @ 0x020642bc, 0x14 bytes, Thumb
 * func_020642a8 @ 0x020642a8, 0x14 bytes, Thumb
 * func_020642a4 @ 0x020642a4, 0x4 bytes, Thumb
 * func_02064294 @ 0x02064294, 0xe bytes, Thumb
 * func_02064290 @ 0x02064290, 0x4 bytes, Thumb
 * func_0206426c @ 0x0206426c, 0x24 bytes, Thumb
 * func_02064244 @ 0x02064244, 0x26 bytes, Thumb
 * func_02064210 @ 0x02064210, 0x32 bytes, Thumb
 * func_020641e0 @ 0x020641e0, 0x2e bytes, Thumb
 * func_020641c8 @ 0x020641c8, 0x18 bytes, Thumb
 * func_020641b0 @ 0x020641b0, 0x18 bytes, Thumb
 * func_02064190 @ 0x02064190, 0x20 bytes, Thumb
 * func_0206418c @ 0x0206418c, 0x4 bytes, Thumb
 * func_02064188 @ 0x02064188, 0x4 bytes, Thumb
 * func_02064170 @ 0x02064170, 0x18 bytes, Thumb
 * func_02064158 @ 0x02064158, 0x18 bytes, Thumb
 * func_02064138 @ 0x02064138, 0x20 bytes, Thumb
 * func_02064134 @ 0x02064134, 0x4 bytes, Thumb
 * func_02064128 @ 0x02064128, 0xc bytes, Thumb
 * func_02064124 @ 0x02064124, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_020641c8 UnkStruct_020641c8;

struct UnkStruct_020641c8 {
    void *vt;
};

typedef struct {
    int *unk_00;
} UnkStruct_02064170;

extern void MI_CpuFill8(void *dst, int val, int size);
extern void MI_CpuCopy8(void *a, void *b, int c);
extern int func_020644cc(int);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern int func_020a87e0(void *, void *);
extern void *func_020a8cac(UnkStruct_020641c8 *self);
extern void *func_020a8c38(void *);
extern char data_020de694[];
extern void func_020edb3c(void *p);
extern void *func_020a88ec(void *arg);
extern unsigned char data_020de67c;
extern void *func_020a887c(void *);

UnkStruct_02064170 *func_02064170(UnkStruct_02064170 *arg);
void *func_02064158(void *arg);
void func_02064128(int p0, int p1, int p2);

void func_020642fc(void *object) {}

void func_020642f8(void *object) {}

void func_020642e0(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    MI_CpuFill8(ptr + 2, 0, 12);
    *(unsigned short *) ptr = 0;
}

void func_020642d0(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0xe);
}

void func_020642bc(void *dest, const void *src)
{
    *(unsigned short *) dest = *(const unsigned short *) src;
    MI_CpuCopy8((void *) ((const char *) src + 2), (char *) dest + 2, 12);
}

void func_020642a8(unsigned short *src, unsigned short *dst)
{
    unsigned short val;
    val = *src;
    *dst = val;
    MI_CpuCopy8(src + 1, dst + 1, 0xc);
}

int func_020642a4(int p0)
{
    return ((int) (p0) + (2));
}

unsigned int func_02064294(const unsigned short *ptr)
{
    unsigned int result;
    unsigned int flag;

    flag = 0;
    if (*ptr != 0) {
        flag = 1;
    }
    result = flag;
    return result;
}

void func_02064290(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

unsigned short func_0206426c(void *receiver)
{
    unsigned short x;

    x = (unsigned short) func_020644cc(0x7fff);
    x |= 0x8000;
    return x;
}

void func_02064244(void *a, void *b)
{
    func_020642e0(a);
    MI_CpuCopy8(b, (void *) ((char *) a + 2), 12);
    *(unsigned short *) a = func_0206426c(a);
}

void func_02064210(void *param0, void *param1)
{
    char local[0x1c];
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_02064170((UnkStruct_02064170 *) local);
    func_020a8874(local, (char *) r5 + 2, 6);
    func_020a8a70(r4, local, 0, 0);
    func_02064158(local);
}

void func_020641e0(void *param0, void *param1)
{
    char local[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02064170((UnkStruct_02064170 *) local);
    func_020a87e0(local, r4);
    func_02064128((int) local, (int) ((char *) r5 + 2), 6);
    func_02064158(local);
}

UnkStruct_020641c8 *func_020641c8(UnkStruct_020641c8 *self)
{
    func_020a8cac(self);
    self->vt = ((char *) data_020de694);
    return self;
}

void *func_020641b0(void *obj)
{
    *(int **) obj = ((int *) data_020de694);
    func_020a8c38(obj);
    return obj;
}

void *func_02064190(void *p)
{
    *(void **) p = data_020de694;
    func_020a8c38(p);
    func_020edb3c(p);
    return p;
}

int func_0206418c(void)
{
    return 14;
}

int func_02064188(int p0)
{
    return ((int) (p0) + (18));
}

UnkStruct_02064170 *func_02064170(UnkStruct_02064170 *arg)
{
    func_020a88ec(arg);
    arg->unk_00 = ((int *) &data_020de67c);
    return arg;
}

void *func_02064158(void *arg)
{
    *(void **) arg = (void *) &data_020de67c;
    func_020a887c(arg);
    return arg;
}

void *func_02064138(void *p)
{
    *(void **) p = &data_020de67c;
    func_020a887c(p);
    func_020edb3c(p);
    return p;
}

int func_02064134(void)
{
    return 6;
}

void func_02064128(int p0, int p1, int p2)
{
    MI_CpuCopy8((void *) ((p0 + 14)), (void *) p1, (p2 << 1));
}

int func_02064124(int p0)
{
    return ((int) (p0) + (14));
}
