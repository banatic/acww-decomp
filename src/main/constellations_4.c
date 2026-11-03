/* constellations_4: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b1a64 @ 0x020b1a64, 0x10 bytes, Thumb
 * func_020b1a54 @ 0x020b1a54, 0x10 bytes, Thumb
 * func_020b1a24 @ 0x020b1a24, 0x30 bytes, Thumb
 * func_020b1a0c @ 0x020b1a0c, 0x16 bytes, Thumb
 * func_020b19e4 @ 0x020b19e4, 0x28 bytes, Thumb
 * func_020b19c8 @ 0x020b19c8, 0x1c bytes, Thumb
 * func_020b19b4 @ 0x020b19b4, 0x14 bytes, Thumb
 * func_020b19a0 @ 0x020b19a0, 0x14 bytes, Thumb
 * func_020b198c @ 0x020b198c, 0x14 bytes, Thumb
 * func_020b1974 @ 0x020b1974, 0x18 bytes, Thumb
 * func_020b1954 @ 0x020b1954, 0x20 bytes, Thumb
 * func_020b193c @ 0x020b193c, 0x18 bytes, Thumb
 * func_020b191c @ 0x020b191c, 0x20 bytes, Thumb
 * func_020b1918 @ 0x020b1918, 0x4 bytes, Thumb
 * func_020b1914 @ 0x020b1914, 0x4 bytes, Thumb
 * func_020b18fc @ 0x020b18fc, 0x18 bytes, Thumb
 * func_020b18e4 @ 0x020b18e4, 0x18 bytes, Thumb
 * func_020b18c4 @ 0x020b18c4, 0x20 bytes, Thumb
 * func_020b18c0 @ 0x020b18c0, 0x4 bytes, Thumb
 * func_020b18bc @ 0x020b18bc, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x1E];
    char someData[0x0C];
    unsigned short array[16];
} UnkStruct_020b1a24;

typedef struct {
    char pad_00[0x4a0];
    unsigned short flag;
} Func020b1974Struct;

typedef struct {
    void *vtable;
} UnkStruct_020b1954;

struct UnkStruct_020b191c {
    unsigned int unk_00;
};

struct Object {
    void *vtable;
};

extern void *func_0209529c(int a);
extern int func_0209526c(void *);
extern void func_02051bf8(void *ptr, int value);
extern void func_02095238(void *ptr);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_020a8cac(UnkStruct_020b1954 *p);
extern void func_020a8c1c(UnkStruct_020b1954 *p);
extern void *func_020a8c38(void *);
extern void func_020edb3c(struct UnkStruct_020b191c *obj);
extern unsigned char data_020e4290[];
extern void *func_020a88ec(void *obj);
extern char data_020e4278;
extern void *func_020a887c(void *obj);

int func_020b1a64(int a)
{
    func_0209529c(a);
    return a;
}

void *func_020b1a54(void *arg)
{
    func_0209526c(arg);
    return arg;
}

void func_020b1a24(UnkStruct_020b1a24 *p)
{
    int i;
    for (i = 0; i < 16; i++) {
        p->array[i] = 0xFFFF;
    }
    func_02051bf8(p->someData, 6);
    func_02095238(p);
}

void *func_020b1a0c(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0x4a);
    return a;
}

int func_020b19e4(int arg)
{
    __cxa_vec_ctor((void *) (arg), 0x10, 0x4A, (((void (*)(void *)) (int (*)(void *)) func_020b1a64)), (((void (*)(void *)) func_020b1a54)));
    return arg;
}

void *func_020b19c8(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 0x10, 0x4a, (((void (*)(void *)) func_020b1a54)));
    return arg;
}

void func_020b19b4(void *arg0)
{
    unsigned short *ptr;
    unsigned short value;

    value = 0;
    ptr = (unsigned short *) ((char *) arg0 + 0x4a0);
    *ptr = value;
    ptr = (unsigned short *) ((char *) arg0 + 0x4a2);
    *ptr = value;
}

void func_020b19a0(unsigned short *ptr, int bit)
{
    ptr[0x250] |= (1 << bit);
}

void func_020b198c(unsigned short *param0, int param1)
{
    unsigned short *ptr;
    unsigned short val;
    int shift;

    ptr = (unsigned short *) ((unsigned int) param0 + 0x4A0);
    val = *ptr;
    shift = 1 << param1;
    val &= ~shift;
    *ptr = val;
}

int func_020b1974(Func020b1974Struct *s, int bit)
{
    int value = s->flag & (1 << bit);
    if (value) {
        return 1;
    } else {
        return 0;
    }
}

UnkStruct_020b1954 *func_020b1954(UnkStruct_020b1954 *p)
{
    func_020a8cac(p);
    p->vtable = ((int *) data_020e4290);
    func_020a8c1c(p);
    return p;
}

void *func_020b193c(void *param)
{
    *(void **) param = ((int *) data_020e4290);
    func_020a8c38(param);
    return param;
}

struct UnkStruct_020b191c *func_020b191c(struct UnkStruct_020b191c *obj)
{
    obj->unk_00 = (unsigned int) data_020e4290;
    func_020a8c38((void *) obj);
    func_020edb3c(obj);
    return obj;
}

int func_020b1918(void)
{
    return 14;
}

int func_020b1914(int p0)
{
    return ((int) (p0) + (18));
}

void *func_020b18fc(void *obj)
{
    func_020a88ec(obj);
    *(void **) obj = (void *) &data_020e4278;
    return obj;
}

struct Object *func_020b18e4(struct Object *obj)
{
    obj->vtable = ((unsigned char *) &data_020e4278);
    func_020a887c(obj);
    return obj;
}

void *func_020b18c4(void *this)
{
    *((void **) this) = &data_020e4278;
    func_020a887c(this);
    func_020edb3c((struct UnkStruct_020b191c *) this);
    return this;
}

int func_020b18c0(void)
{
    return 6;
}

int func_020b18bc(int p0)
{
    return ((int) (p0) + (14));
}
