/* paired_town: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02088460 @ 0x02088460, 0x10 bytes, Thumb
 * func_02088450 @ 0x02088450, 0x10 bytes, Thumb
 * func_02088404 @ 0x02088404, 0x4c bytes, Thumb
 * func_020883cc @ 0x020883cc, 0x36 bytes, Thumb
 * func_02088394 @ 0x02088394, 0x36 bytes, Thumb
 * func_02088368 @ 0x02088368, 0x2c bytes, Thumb
 * func_02088318 @ 0x02088318, 0x50 bytes, Thumb
 * func_020882f0 @ 0x020882f0, 0x26 bytes, Thumb
 * func_020882ec @ 0x020882ec, 0x2 bytes, Thumb
 * func_020882e4 @ 0x020882e4, 0x8 bytes, Thumb
 * func_020882dc @ 0x020882dc, 0x8 bytes, Thumb
 * func_020882cc @ 0x020882cc, 0xe bytes, Thumb
 * func_020882c4 @ 0x020882c4, 0x8 bytes, Thumb
 * func_020882b0 @ 0x020882b0, 0x12 bytes, Thumb
 * func_0208829c @ 0x0208829c, 0x12 bytes, Thumb
 * func_02088290 @ 0x02088290, 0xa bytes, Thumb
 * func_02088284 @ 0x02088284, 0xa bytes, Thumb
 */

struct UnkStruct_020882f0 {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
};

struct UnkStruct_0208829c {
    unsigned char pad_00[0xe];
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
};

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flags;
} UnkStruct_02088290;

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flags;
} UnkStruct_02088284;

extern void func_020642fc(void *object);
extern void func_020642f8(void *object);
extern char data_021dc7a8[];
extern char data_021f3b8a;
extern int func_020984e8(void);
extern unsigned int func_02099688(unsigned int);
extern int func_020e8b0c(int, int, int);
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int len);
extern void func_02098fd0(int a, int b);
extern void func_020642e0(void *ptr);
extern void func_020642d0(void *, void *);

void func_02088318(void);
void func_020882f0(struct UnkStruct_020882f0 *param);
int func_020882dc(unsigned char *p0);
void func_020882cc(unsigned char *addr, unsigned char val);
int func_020882c4(unsigned char *p0);

int func_02088460(int arg)
{
    func_020642fc((void *) arg);
    return arg;
}

void *func_02088450(void *p)
{
    func_020642f8(p);
    return p;
}

void func_02088404(int arg)
{
    char *base;
    int diff;

    if (arg < 1) {
        return;
    }
    base = data_021dc7a8;
    diff = func_020882dc((unsigned char *) ((int) &data_021f3b8a)) - arg;
    if (diff < 0) {
        diff = 0;
    }
    if (diff <= 0) {
        func_020882f0((struct UnkStruct_020882f0 *) (base + 0x173e2));
    } else {
        func_020882cc((unsigned char *) (base + 0x173e2), (unsigned char) diff);
    }
    func_02088318();
}

int func_020883cc(void)
{
    unsigned int tested_value0;
    int r4;
    int result;

    if ((tested_value0 = (unsigned int) (func_020984e8())) != 0) {
        r4 = func_02099688(tested_value0);
        if (func_020882c4((unsigned char *) r4) == 0) {
            result = func_020e8b0c(func_020882dc((unsigned char *) r4), 1, 7);
            if (result != 0) {
                return 1;
            }
        }
    }
    return 0;
}

int func_02088394(void)
{
    unsigned int tested_value0;
    if ((tested_value0 = (unsigned int) (func_020984e8())) != 0) {
        int tmp = func_02099688(tested_value0);
        if (func_020882c4((unsigned char *) tmp) == 1) {
            int arg = func_020882dc((unsigned char *) tmp);
            if (func_020e8b0c(arg, 1, 7) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void func_02088368(void)
{
    char *base = ((char *) data_021dc7a8);
    void *p = (void *) func_020984e8();
    if (p && base) {
        MI_CpuCopy8((void *) func_02099688((unsigned int) p), base + 0x173e2, 16);
    }
}

void func_02088318(void)
{
    int a;
    int b;
    int c;
    char *base;

    base = (char *) data_021dc7a8;
    a = func_020984e8();
    if (a == 0 || base == 0) {
        return;
    }
    b = (int) func_02099688(a);
    MI_CpuCopy8((const void *) (base + 0x173e2), (void *) b, 0x10);
    c = func_020882dc((unsigned char *) (base + 0x173e2));
    if (func_020e8b0c(c, 1, 7) == 0) {
        func_02098fd0(a, 0x33);
    }
}

void func_020882f0(struct UnkStruct_020882f0 *param)
{
    func_020642e0(param);
    param->unk_0E &= ~0x0f;
    param->unk_0E &= ~0x10;
    param->unk_0E &= ~0x20;
}

void *func_020882ec(void *record)
{
    return record;
}

void func_020882e4(void *argument0, void *argument1)
{
    func_020642d0((void *) argument0, (void *) argument1);
}

int func_020882dc(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[14] << 28)) >> 28);
}

void func_020882cc(unsigned char *addr, unsigned char val)
{
    addr[0xe] = (addr[0xe] & ~0x0f) | (val & 0x0f);
}

int func_020882c4(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[14] << 27)) >> 31);
}

void func_020882b0(unsigned char *ptr, unsigned int flag)

{

    ptr[0xe] = (ptr[0xe] & ~0x10) | ((flag & 1) << 4);
}

int func_0208829c(struct UnkStruct_0208829c *s)
{
    if (s->bit5) {
        return 1;
    } else {
        return 0;
    }
}

void func_02088290(UnkStruct_02088290 *p)
{
    p->flags |= 0x20;
}

void func_02088284(UnkStruct_02088284 *p)
{
    p->flags &= ~0x20;
}
