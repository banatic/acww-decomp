/* scene_claim_3: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d9c4 @ 0x0209d9c4, 0x10 bytes, Thumb
 * func_0209d9a8 @ 0x0209d9a8, 0x1c bytes, Thumb
 * func_0209d9a0 @ 0x0209d9a0, 0x6 bytes, Thumb
 * func_0209d988 @ 0x0209d988, 0x16 bytes, Thumb
 * func_0209d970 @ 0x0209d970, 0x16 bytes, Thumb
 * func_0209d95c @ 0x0209d95c, 0x14 bytes, Thumb
 * func_0209d938 @ 0x0209d938, 0x24 bytes, Thumb
 * func_0209d934 @ 0x0209d934, 0x2 bytes, Thumb
 * func_0209d918 @ 0x0209d918, 0x1c bytes, Thumb
 * func_0209d8fc @ 0x0209d8fc, 0x1c bytes, Thumb
 * func_0209d8e4 @ 0x0209d8e4, 0x16 bytes, Thumb
 * func_0209d8cc @ 0x0209d8cc, 0x16 bytes, Thumb
 * func_0209d8b0 @ 0x0209d8b0, 0x1a bytes, Thumb
 * func_0209d8a0 @ 0x0209d8a0, 0x10 bytes, Thumb
 * func_0209d89c @ 0x0209d89c, 0x2 bytes, Thumb
 * func_0209d854 @ 0x0209d854, 0x48 bytes, Thumb
 * func_0209d850 @ 0x0209d850, 0x4 bytes, Thumb
 * func_0209d848 @ 0x0209d848, 0x6 bytes, Thumb
 * func_0209d844 @ 0x0209d844, 0x4 bytes, Thumb
 * func_0209d840 @ 0x0209d840, 0x4 bytes, Thumb
 * func_0209d83c @ 0x0209d83c, 0x4 bytes, Thumb
 * func_0209d838 @ 0x0209d838, 0x4 bytes, Thumb
 * func_0209d830 @ 0x0209d830, 0x6 bytes, Thumb
 * func_0209d82c @ 0x0209d82c, 0x4 bytes, Thumb
 * func_0209d81c @ 0x0209d81c, 0xe bytes, Thumb
 * func_0209d818 @ 0x0209d818, 0x4 bytes, Thumb
 * func_0209d808 @ 0x0209d808, 0xe bytes, Thumb
 * func_0209d7e8 @ 0x0209d7e8, 0x20 bytes, Thumb
 * func_0209d7c8 @ 0x0209d7c8, 0x20 bytes, Thumb
 * func_0209d780 @ 0x0209d780, 0x46 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_0209d9a0;

typedef struct {
    unsigned char pad_00[32];
    unsigned char unk_20;
} UnkStruct_0209d848;

typedef struct {
    unsigned char pad_00[32];
    unsigned char unk_20;
} UnkStruct_0209d830;

typedef struct {
    int a, b, c;
} Src;

typedef struct {
    int pad_00[4];
    int a, b, c;
} Dest;

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern char data_021fbee8[];
extern unsigned char data_021dc6e8[];
extern unsigned char data_021dc70c[];
extern unsigned char data_020d1ad8[];
extern int func_020b5e10(void);
extern int func_020b6140(int, int, void *, void *, void *, void *, void *, void *, int, int);

void func_0209d9a0(UnkStruct_0209d9a0 *p);
void func_0209d934(void *object);
void func_0209d854(void *obj);
void func_0209d83c(unsigned char *p0, int p1);
void func_0209d838(unsigned char *p0, int p1);
void func_0209d830(UnkStruct_0209d830 *p, unsigned char v);
void func_0209d82c(unsigned char *p0, int p1);
void func_0209d81c(unsigned int *dest, const unsigned int *src);
void func_0209d818(unsigned short *p0, int p1);
void func_0209d808(Dest *dest, const Src *src);

void *func_0209d9c4(void *arg)
{
    func_0209d9a0((UnkStruct_0209d9a0 *) arg);
    return arg;
}

void *func_0209d9a8(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 0x33, 1, (void (*)(void *)) func_0209d934);
    return arg;
}

void func_0209d9a0(UnkStruct_0209d9a0 *p)
{
    p->unk_00 = 0;
}

void func_0209d988(unsigned char *p, int bit)
{
    *p |= 1 << (bit & 3);
}

void func_0209d970(unsigned char *r0, int r1)
{
    unsigned char r4;
    int r3;
    int r2;

    r4 = *r0;
    r3 = 1;
    r2 = 3;
    r1 &= r2;
    r3 <<= r1;
    r4 &= ~r3;
    *r0 = r4;
}

int func_0209d95c(const unsigned char *data, int shift)
{
    if ((data[0] >> (shift & 3)) & 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_0209d938(void *param)
{
    int count = 0;
    unsigned int i = count;
    do {
        if (func_0209d95c((const unsigned char *) param, i)) {
            count++;
        }
        i++;
    } while (i < 4);
    return count;
}

void func_0209d934(void *object) {}

int func_0209d918(unsigned char *p0, int p1)
{
    unsigned char buf[4];
    buf[0] = p0[0];
    func_0209d988(buf, p1);
    return func_0209d938(buf);
}

void func_0209d8fc(char *p)
{
    unsigned int i;
    for (i = 0; i < 51; i++) {
        func_0209d9a0((UnkStruct_0209d9a0 *) (p + i));
    }
}

void func_0209d8e4(int a, unsigned int b, int c)
{
    if (b < 0x33) {
        func_0209d988((unsigned char *) (a + b), c);
    }
}

void func_0209d8cc(int a, unsigned int b, int c)
{
    if (b >= 0x33) {
        return;
    }
    func_0209d970((unsigned char *) (a + b), c);
}

int func_0209d8b0(int a, unsigned int b, int c)
{
    if (b < 0x33) {
        return func_0209d918((unsigned char *) (a + b), c);
    }
    return 0;
}

int func_0209d8a0(int a)
{
    int tmp;
    tmp = a;
    func_0209d854((void *) a);
    return tmp;
}

void func_0209d89c(void *object) {}

void func_0209d854(void *obj)
{
    func_0209d83c((unsigned char *) obj, 2);
    func_0209d838((unsigned char *) obj, -1);
    func_0209d830((UnkStruct_0209d830 *) obj, 0);
    func_0209d82c((unsigned char *) obj, 0);
    func_0209d81c((unsigned int *) obj, (const unsigned int *) data_021fbee8);
    func_0209d818((unsigned short *) obj, 0);
    func_0209d808((Dest *) obj, (const Src *) data_021fbee8);
}

int func_0209d850(unsigned char *p0)
{
    return p0[31];
}

unsigned char func_0209d848(UnkStruct_0209d848 *p)
{
    return p->unk_20;
}

int func_0209d844(int p0)
{
    return ((int) (p0) + (4));
}

int func_0209d840(int p0)
{
    return ((int) (p0) + (16));
}

void func_0209d83c(unsigned char *p0, int p1)
{
    p0[31] = p1;
}

void func_0209d838(unsigned char *p0, int p1)
{
    p0[30] = p1;
}

void func_0209d830(UnkStruct_0209d830 *p, unsigned char v)
{
    p->unk_20 = v;
}

void func_0209d82c(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_0209d81c(unsigned int *dest, const unsigned int *src)
{
    dest[1] = src[0];
    dest[2] = src[1];
    dest[3] = src[2];
}

void func_0209d818(unsigned short *p0, int p1)
{
    p0[14] = p1;
}

void func_0209d808(Dest *dest, const Src *src)
{
    dest->a = src->a;
    dest->b = src->b;
    dest->c = src->c;
}

void func_0209d7e8(void)
{
    func_0209d854((void *) data_021dc6e8);
    func_0209d8fc((char *) ((void *) data_021dc70c));
}

int func_0209d7c8(int param)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        if (param == data_020d1ad8[i * 2]) {
            return 1;
        }
    }
    return 0;
}

int func_0209d780(int param1)
{
    unsigned char arr[4];
    int localC;
    int localB;
    long long localA;
    if (func_020b6140(func_020b5e10(), param1, arr, &localA, &localB, &localC, &arr[2], &arr[1], 0, 0)) {
        return func_0209d7c8(arr[0]);
    }
    return 0;
}
