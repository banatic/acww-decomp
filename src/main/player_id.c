/* player_id: 24 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020950d4 @ 0x020950d4, 0x24 bytes, Thumb
 * func_020950d0 @ 0x020950d0, 0x4 bytes, Thumb
 * func_020950cc @ 0x020950cc, 0x4 bytes, Thumb
 * func_020950c8 @ 0x020950c8, 0x4 bytes, Thumb
 * func_020950c0 @ 0x020950c0, 0x6 bytes, Thumb
 * func_020950ac @ 0x020950ac, 0x14 bytes, Thumb
 * func_020950a8 @ 0x020950a8, 0x4 bytes, Thumb
 * func_02095074 @ 0x02095074, 0x34 bytes, Thumb
 * func_02095044 @ 0x02095044, 0x30 bytes, Thumb
 * func_02095040 @ 0x02095040, 0x2 bytes, Thumb
 * func_02095038 @ 0x02095038, 0x8 bytes, Thumb
 * func_02094ffc @ 0x02094ffc, 0x3c bytes, Thumb
 * func_02094fec @ 0x02094fec, 0x10 bytes, Thumb
 * func_02094fd4 @ 0x02094fd4, 0x18 bytes, Thumb
 * func_02094fbc @ 0x02094fbc, 0x18 bytes, Thumb
 * func_02094f9c @ 0x02094f9c, 0x20 bytes, Thumb
 * func_02094f98 @ 0x02094f98, 0x4 bytes, Thumb
 * func_02094f94 @ 0x02094f94, 0x4 bytes, Thumb
 * func_02094f7c @ 0x02094f7c, 0x18 bytes, Thumb
 * func_02094f64 @ 0x02094f64, 0x18 bytes, Thumb
 * func_02094f44 @ 0x02094f44, 0x20 bytes, Thumb
 * func_02094f40 @ 0x02094f40, 0x4 bytes, Thumb
 * func_02094f34 @ 0x02094f34, 0xc bytes, Thumb
 * func_02094f30 @ 0x02094f30, 0x4 bytes, Thumb
 */

struct UnkStruct_02094ffc {
    unsigned short id;
    unsigned char tail[12];
};

struct UnkStruct_02094fbc {
    void *unk_00;
};

typedef struct {
    void *vtbl;
} UnkStruct_02094f7c;

typedef struct UnkStruct_02094f44 UnkStruct_02094f44;

struct UnkStruct_02094f44 {
    void *vtable;
};

extern __arm unsigned int func_020644cc(unsigned int);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern int func_020a87e0(void *, void *);
extern void func_020642d0(void *, void *);
extern int func_02064294(void *p);
extern int memcmp(void *p1, void *p2, unsigned int size);
extern struct UnkStruct_02094ffc data_021dc7aa;
extern int func_0209871c(void *arg1, void *arg2);
extern unsigned char data_021dc7bc[];
extern void *func_020a8cac(void *);
extern char data_020e2f6c[];
void *func_020a8c38(struct UnkStruct_02094fbc *arg);
extern void func_020edb3c(void *obj);
extern void *func_020a88ec(void *obj);
extern void *func_020a887c(void *);
extern char data_020e2f54[];

void *func_02094f7c(void *obj);
void *func_02094f64(void *arg);
void func_02094f34(void *r0, int r1, int r2);

unsigned short func_020950d4(void)
{
    unsigned short t = (unsigned short) func_020644cc(0x7ffc);
    return (unsigned short) (t | 0x8000);
}

int func_020950d0(unsigned short *p0)
{
    return p0[7];
}

void func_020950cc(unsigned short *p0, int p1)
{
    p0[7] = p1;
}

void func_020950c8(unsigned char *p0, int p1)
{
    p0[28] = p1;
}

int func_020950c0(signed char *p)
{
    return p[28];
}

void func_020950ac(void *a, void *b)
{
    void *dst = (char *) a + 0x10;
    MI_CpuCopy8(b, dst, 0xc);
}

int func_020950a8(int p0)
{
    return ((int) (p0) + (16));
}

void *func_02095074(void *param0, void *param1)
{
    unsigned char sp[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02094f7c(sp);
    func_020a8874(sp, (char *) r5 + 0x10, 6);
    func_020a8a70(r4, sp, 0, 0);
    return func_02094f64(sp);
}

void func_02095044(void *param0, void *param1)
{
    unsigned char sp[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02094f7c(sp);
    func_020a87e0(sp, r4);
    func_02094f34(sp, (int) ((char *) r5 + 0x10), 6);
    func_02094f64(sp);
}

void *func_02095040(void *object)
{
    return object;
}

void func_02095038(void *argument0, void *argument1)
{
    func_020642d0((void *) argument0, (void *) argument1);
}

int func_02094ffc(struct UnkStruct_02094ffc *p)
{
    int result = 2;
    if (func_02064294(p) != 0) {
        struct UnkStruct_02094ffc *q = &data_021dc7aa;
        if (p->id == q->id && memcmp(p->tail, q->tail, 0xc) == 0) {
            result = 0;
        } else {
            result = 1;
        }
    }
    return result;
}

int func_02094fec(void *arg0)
{
    return func_0209871c((void *) data_021dc7bc, arg0);
}

void *func_02094fd4(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = ((unsigned char *) data_020e2f6c);
    return obj;
}

struct UnkStruct_02094fbc *func_02094fbc(struct UnkStruct_02094fbc *arg)
{
    arg->unk_00 = &data_020e2f6c;
    func_020a8c38(arg);
    return arg;
}

void *func_02094f9c(void *obj)
{
    *((void **) obj) = (void *) ((int *) data_020e2f6c);
    func_020a8c38((struct UnkStruct_02094fbc *) obj);
    func_020edb3c(obj);
    return obj;
}

int func_02094f98(void *object)
{
    (void) object;
    return 14;
}

int func_02094f94(int p0)
{
    return ((int) (p0) + (18));
}

void *func_02094f7c(void *obj)
{
    func_020a88ec(obj);
    ((UnkStruct_02094f7c *) obj)->vtbl = ((int *) data_020e2f54);
    return obj;
}

void *func_02094f64(void *arg)
{
    *(unsigned int *) arg = (unsigned int) ((int *) data_020e2f54);
    func_020a887c(arg);
    return arg;
}

UnkStruct_02094f44 *func_02094f44(UnkStruct_02094f44 *p)
{
    p->vtable = data_020e2f54;
    func_020a887c(p);
    func_020edb3c(p);
    return p;
}

int func_02094f40(void *object)
{
    return 6;
}

void func_02094f34(void *r0, int r1, int r2)
{
    MI_CpuCopy8((char *) r0 + 0xe, (const void *) r1, r2 << 1);
}

int func_02094f30(int p0)
{
    return ((int) (p0) + (14));
}
