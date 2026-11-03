/* field_actor_states_19: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c01c @ 0x0200c01c, 0x34 bytes, Thumb
 * func_0200c00c @ 0x0200c00c, 0x10 bytes, Thumb
 * func_0200bf58 @ 0x0200bf58, 0xb4 bytes, Thumb
 * func_0200bf10 @ 0x0200bf10, 0x48 bytes, Thumb
 * func_0200bef0 @ 0x0200bef0, 0x20 bytes, Thumb
 * func_0200beb8 @ 0x0200beb8, 0x36 bytes, Thumb
 * func_0200bea4 @ 0x0200bea4, 0x14 bytes, Thumb
 * func_0200be98 @ 0x0200be98, 0xc bytes, Thumb
 * func_0200be5c @ 0x0200be5c, 0x3c bytes, Thumb
 * func_0200be34 @ 0x0200be34, 0x28 bytes, Thumb
 * func_0200be18 @ 0x0200be18, 0x1a bytes, Thumb
 * func_0200be0c @ 0x0200be0c, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[12];
    volatile int id;
} Child;

typedef struct {
    unsigned char pad_00[0x2e4];
    unsigned char unk_2E4;
    unsigned char pad_2E5[0x7d4 - 0x2e4 - 1];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
} UnkStruct_0200bf10;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_0200be0c;

extern void func_0200c0c8(unsigned char *p, unsigned char *a, unsigned char *b);
extern int func_0200c0dc(unsigned char *p, unsigned char a, unsigned char b, int n, int v);
extern void func_0201a484(int arg);
extern int func_0205cb80(unsigned char *);
extern void func_0201a48c(unsigned char *, unsigned char *, int, int, int);
extern void func_02010f5c(unsigned char *);
extern int func_02056f94(unsigned char *);
extern void func_02010a24(unsigned char *, int, int, int, int, int, int, int);
extern void func_0201a698(unsigned char *, void *, int);
extern int func_0200c3b0(unsigned char *, int, int, int);
extern unsigned char data_020c7600[];
extern int func_0200c9a8(UnkStruct_0200bf10 *s, unsigned char val, int a, int b);
extern int func_0200f554(void *arg);
extern void func_02010d64(void *arg);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109a0(int, int, int, unsigned short);
extern int func_02056f28(void *, int);
extern int func_020912d4(int, void *, int, int);
extern int func_0200f328(void *, int);

void func_0200c01c(unsigned char *p, int v)
{
    unsigned char buf[2];
    func_0200c0c8(p + 0x8f0, &buf[0], &buf[1]);
    func_0200c0dc(p, buf[0], buf[1], 5, v);
}

void func_0200c00c(int arg)
{
    func_0201a484(arg + 0x90c);
}

void func_0200bf58(unsigned char *self)
{
    func_0201a48c(self + 0x90c, self + 0x6e0, *(signed short *) (self + 0x8e), func_0205cb80(self + 0x700),
                  (*(unsigned int *) (self + 0x2d8) << 4) >> 16);
    func_02010f5c(self);
    if (func_02056f94(self + 0x2d0) != 0) {
        Child *p = *(Child **) (self + 0x908);
        if (p->id != 0x137) {
            func_02010a24(self, 0x12, 0, 0, 0x1000, 0, 0, p->id);
            func_0201a698(self + 0x90c, p, 1);
        } else {
            func_0200c3b0(self, data_020c7600[*(unsigned char *) (self + 0x7d4) - 1], 5, -1);
        }
    }
}

void func_0200bf10(UnkStruct_0200bf10 *s)
{
    unsigned char *p = &s->unk_7D4;
    unsigned char *q = p + 1;
    if (*q != 0) {
        *q = *q - 1;
    }
    if (s->unk_2E4 != 0) {
        return;
    }
    if (*q != 0) {
        return;
    }
    func_0200c9a8(s, data_020c7600[*p - 1], 5, -1);
}

void func_0200bef0(void *arg)
{
    func_0200bf58((unsigned char *) arg);
    func_0200f554(arg);
    func_02010d64(arg);
    func_0200bf10((UnkStruct_0200bf10 *) arg);
}

void *func_0200beb8(void *param0, void *param1, void *param2)
{
    void *sp[8];
    void *result;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x15, param1, param2);
    result = func_0200e894(param0, sp);
    func_0200e91c(sp);
    return result;
}

void func_0200bea4(int a, void *message, int previous)
{
    func_020109a0(a, 0x9d, 3, 0);
}

void func_0200be98(int a, int b)
{
    func_0200beb8((void *) a, (void *) 5, (void *) b);
}

void func_0200be5c(void *self)
{
    int zero = 0;
    func_02010f5c((unsigned char *) self);
    if (func_02056f28((char *) self + 0x2d0, 6)) {
        func_020912d4(0x50, (char *) self + 0x6e0, zero, zero);
        func_0200f328(self, 0x68);
    }
}

int func_0200be34(int object)
{
    int result = func_02056f94((unsigned char *) (object + 0x2d0));
    if (result != 0) {
        result = func_0200c3b0((unsigned char *) object, 5, 5, -1);
    }
    return result;
}

void func_0200be18(void *ptr)
{
    func_0200be5c(ptr);
    func_02010d64(ptr);
    func_0200be34((int) ptr);
}

void func_0200be0c(UnkStruct_0200be0c *out, const unsigned int *src, unsigned int val)
{
    out->unk_04 = (unsigned char) src[0];
    out->unk_05 = (unsigned char) src[1];
    out->unk_00 = val;
}
