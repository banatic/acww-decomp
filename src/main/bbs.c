/* bbs: 38 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020782d4 @ 0x020782d4, 0x2 bytes, Thumb
 * func_020782d0 @ 0x020782d0, 0x2 bytes, Thumb
 * func_020782cc @ 0x020782cc, 0x2 bytes, Thumb
 * func_020782a0 @ 0x020782a0, 0x2c bytes, Thumb
 * func_02078298 @ 0x02078298, 0x6 bytes, Thumb
 * func_02078290 @ 0x02078290, 0x6 bytes, Thumb
 * func_02078288 @ 0x02078288, 0x6 bytes, Thumb
 * func_02078268 @ 0x02078268, 0x20 bytes, Thumb
 * func_02078248 @ 0x02078248, 0x1e bytes, Thumb
 * func_02078234 @ 0x02078234, 0x14 bytes, Thumb
 * func_02078224 @ 0x02078224, 0x10 bytes, Thumb
 * func_020781fc @ 0x020781fc, 0x28 bytes, Thumb
 * func_020781e0 @ 0x020781e0, 0x1c bytes, Thumb
 * func_020781d8 @ 0x020781d8, 0x8 bytes, Thumb
 * func_020781d0 @ 0x020781d0, 0x8 bytes, Thumb
 * func_020781bc @ 0x020781bc, 0x14 bytes, Thumb
 * func_02078194 @ 0x02078194, 0x28 bytes, Thumb
 * func_02078188 @ 0x02078188, 0xc bytes, Thumb
 * func_02078148 @ 0x02078148, 0x40 bytes, Thumb
 * func_0207813c @ 0x0207813c, 0xc bytes, Thumb
 * func_02078130 @ 0x02078130, 0xc bytes, Thumb
 * func_020780f0 @ 0x020780f0, 0x40 bytes, Thumb
 * func_020780d0 @ 0x020780d0, 0x20 bytes, Thumb
 * func_020780b8 @ 0x020780b8, 0x18 bytes, Thumb
 * func_02078098 @ 0x02078098, 0x20 bytes, Thumb
 * func_02078094 @ 0x02078094, 0x4 bytes, Thumb
 * func_02078090 @ 0x02078090, 0x4 bytes, Thumb
 * func_02078070 @ 0x02078070, 0x20 bytes, Thumb
 * func_02078058 @ 0x02078058, 0x18 bytes, Thumb
 * func_02078040 @ 0x02078040, 0x18 bytes, Thumb
 * func_02078020 @ 0x02078020, 0x20 bytes, Thumb
 * func_0207801c @ 0x0207801c, 0x4 bytes, Thumb
 * func_02078018 @ 0x02078018, 0x4 bytes, Thumb
 * func_02077f8c @ 0x02077f8c, 0x8a bytes, Thumb
 * func_02077f3c @ 0x02077f3c, 0x50 bytes, Thumb
 * func_02077f14 @ 0x02077f14, 0x28 bytes, Thumb
 * func_02077ed4 @ 0x02077ed4, 0x40 bytes, Thumb
 * func_02077ec4 @ 0x02077ec4, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[192];
    unsigned char unk_C0;
} UnkStruct_02078298;

typedef struct {
    unsigned char pad_00[193];
    unsigned char unk_C1;
} UnkStruct_02078290;

typedef struct {
    unsigned char pad_00[194];
    unsigned char unk_C2;
} UnkStruct_02078288;

typedef struct {
    char pad_00[0xC3];
    unsigned char flag;
} UnkStruct_02078234;

typedef struct {
    void *unk_00;
} UnkStruct_020780b8;

extern void func_02051bf8(void *param1, void *param2);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned int data_020e1858;
extern void MI_CpuCopy8(unsigned char *dst, const unsigned char *src, unsigned int size);
extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020e1888;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);
extern unsigned char data_021f43ec;
extern int func_0203d7d8(int a, unsigned char *p, int c);
extern void *func_020a88ec(void *ptr);
extern int data_020e1870;
extern void *func_020a887c(void *self);
extern void *func_02070c08(void *);
extern void *func_020707d0(void *);
extern int func_020a7bf4(void *, int);
extern int func_020a8a34(void *, int);
extern int func_020a87e0(void *, void *);
extern int func_0205182c(void *, short *, int);
extern int func_02070784(void *);
extern void *func_020707b8(void *);
extern int **func_02070be8(void *);
extern void func_0209df64(void *);
extern unsigned char data_021eed68[];

void func_020780f0(unsigned char *base, int start);
void *func_02077f14(int a, int b);

void func_020782d4(void *object) {}

void func_020782d0(void *object) {}

unsigned short *func_020782cc(void *record)
{
    return (unsigned short *) record;
}

void func_020782a0(void *param1, void *param2)
{
    unsigned char *dst;
    unsigned char *src;
    unsigned char val;

    src = (unsigned char *) param2;
    dst = (unsigned char *) param1;

    val = src[0];
    dst[0xc0] = val;
    val = src[1];
    dst[0xc1] = val;
    val = src[2];
    dst[0xc2] = val;
    dst[0xc3] = 0;

    func_02051bf8(param1, (void *) 0x60);
}

unsigned char func_02078298(UnkStruct_02078298 *p)
{
    return p->unk_C0;
}

unsigned char func_02078290(UnkStruct_02078290 *p)
{
    return p->unk_C1;
}

unsigned char func_02078288(UnkStruct_02078288 *p)
{
    return p->unk_C2;
}

int func_02078268(unsigned char *ptr, int bit)
{
    if (bit < 0 || bit >= 4) {
        return 1;
    }
    return (ptr[0xc3] & (1 << bit)) ? 1 : 0;
}

void func_02078248(unsigned char *p, int n)
{
    if (n < 0 || n >= 4) {
        return;
    }
    p[0xc3] |= (unsigned char) (1 << n);
}

int func_02078234(UnkStruct_02078234 *s)
{
    if (s->flag & 0x10) {
        return 1;
    }
    return 0;
}

void func_02078224(unsigned char *param)
{
    unsigned char temp;
    unsigned char *ptr;

    ptr = param + 0xc3;
    temp = *ptr;
    temp |= 0x10;
    *ptr = temp;
}

int func_020781fc(int arg0)
{
    __cxa_vec_ctor((void *) (arg0), 15, 196, (void (*)(void *)) func_020782d4, (void (*)(void *)) func_020782d0);
    return arg0;
}

void *func_020781e0(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 0xf, 0xc4, (void (*)(void *)) func_020782d0);
    return arg;
}

void *func_020781d8(unsigned char *p, int i)
{
    return (p) + i * 196;
}

void *func_020781d0(unsigned char *argument0, int argument1)
{
    return func_020781d8((unsigned char *) argument0, (int) argument1);
}

// placeholder for literal 0x0b7e
// placeholder for literal 0x0b7c
void func_020781bc(void *r0)
{
    unsigned char *byte_ptr;
    unsigned short *short_ptr;
    byte_ptr = (unsigned char *) r0 + 0x0b7e;
    short_ptr = (unsigned short *) r0 + 0x0b7c / 2;
    *byte_ptr = 0;
    *short_ptr = 0;
}

void func_02078194(void *object)
{
    func_020781bc(object);
    func_02077f14(0, data_020e1858);
    func_02077f14(1, data_020e1858);
}

unsigned char func_02078188(unsigned char *r0)
{
    return r0[0x0b7e];
}

unsigned char *func_02078148(unsigned char *self)
{
    unsigned char count = *((unsigned char *) self + 0xb7e);
    if (count < 15) {
        *((unsigned char *) self + 0xb7e) = count + 1;
        return self + 196 * (*((unsigned char *) self + 0xb7e) - 1);
    } else {
        func_020780f0((unsigned char *) self, 0);
        *((unsigned char *) self + 0xb7e) = 15;
        return self + 196 * (*((unsigned char *) self + 0xb7e) - 1);
    }
}

unsigned short func_0207813c(void *ptr)
{
    return *(unsigned short *) ((char *) ptr + 0xb7c);
}

void func_02078130(short *arg0, short arg1)
{
    arg0[0x5be] = arg1;
}

void func_020780f0(unsigned char *base, int start)
{
    int i;

    for (i = start; i < base[0xb7e] - 1; i++) {
        MI_CpuCopy8(base + (i + 1) * 0xc4, base + i * 0xc4, 0xc4);
    }

    base[0xb7e]--;
}

void *func_020780d0(void *a)
{
    func_020a8cac(a);
    *(void **) a = (void *) &data_020e1888;
    func_020a8c1c(a);
    return a;
}

UnkStruct_020780b8 *func_020780b8(UnkStruct_020780b8 *obj)
{
    obj->unk_00 = &data_020e1888;
    func_020a8c38(obj);
    return obj;
}

void *func_02078098(void *p)
{
    *((void **) p) = (void *) ((unsigned char *) &data_020e1888);
    func_020a8c38(p);
    func_020edb3c(p);
    return p;
}

int func_02078094(void)
{
    return 194;
}

int func_02078090(int p0)
{
    return ((int) (p0) + (18));
}

void func_02078070(int a, int b, int c)
{
    unsigned char t[4];
    t[0] = data_021f43ec;
    t[0] = (unsigned char) b;
    func_0203d7d8(a, t, c);
}

void *func_02078058(void *ptr)
{
    func_020a88ec(ptr);
    *(unsigned int *) ptr = (unsigned int) &data_020e1870;
    return ptr;
}

void *func_02078040(void *self)
{
    *(void **) self = ((char *) &data_020e1870);
    func_020a887c(self);
    return self;
}

void *func_02078020(void *obj)
{
    *(int **) obj = &data_020e1870;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}

int func_0207801c(void)
{
    return 96;
}

int func_02078018(int p0)
{
    return ((int) (p0) + (14));
}

int func_02077f8c(int a, void *b)
{
    char v1[0x6c];
    char v2[0x60];
    short *p;
    int cnt;
    int i;
    func_02070c08(v1);
    func_020707d0(v2);
    p = (short *) func_020782cc((void *) a);
    cnt = 0;
    for (i = cnt; i < 6; i++) {
        int r = func_020a7bf4((char *) b + 0x12, i);
        if (r != 0) {
            int n;
            func_020a8a34(v1, r);
            func_020a87e0(v2, v1);
            func_0205182c(v2, p + cnt, 0x10);
            n = func_02070784(v2);
            cnt += n;
            if (n != 0x10) {
                p[cnt] = 0xa;
                cnt++;
            }
        } else {
            func_020a8c1c(v1);
            p[cnt] = 0xa;
            cnt++;
        }
    }
    func_020707b8(v2);
    func_02070be8(v1);
    return 1;
}

void *func_02077f3c(int a, int b, unsigned char c, unsigned char d, unsigned char e)
{
    struct {
        unsigned char x;
        unsigned char y;
        unsigned char z;
    } small;
    int buf[54];
    int temp;

    func_020780d0(buf);
    func_02078070((int) buf, a, b);
    temp = (int) func_02078148((unsigned char *) (((int *) data_021eed68)));
    small.z = c;
    small.y = d;
    small.x = e;
    func_020782a0((void *) temp, &small);
    func_02077f8c(temp, buf);
    return (void *) func_020780b8((UnkStruct_020780b8 *) buf);
}

void *func_02077f14(int a, int b)
{
    unsigned char buffer[3];
    func_0209df64(buffer);
    return func_02077f3c(a, b, buffer[2], buffer[1], buffer[0]);
}

void func_02077ed4(void *param)
{
    void *handle;
    int local;

    handle = (void *) func_02078148((unsigned char *) ((void *) data_021eed68));
    func_0209df64((void *) (&local));
    func_020782a0(handle, (void *) (&local));
    func_02078224((unsigned char *) handle);
    MI_CpuCopy8((unsigned char *) param, (const unsigned char *) (func_020782cc(handle)), 0xc0);
}

unsigned char func_02077ec4(void)
{
    return func_02078188((unsigned char *) ((void *) data_021eed68));
}
