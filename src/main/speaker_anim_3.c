/* speaker_anim_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020169a8 @ 0x020169a8, 0x10 bytes, Thumb
 * func_02016998 @ 0x02016998, 0x10 bytes, Thumb
 * func_0201691c @ 0x0201691c, 0x7c bytes, Thumb
 * func_020168e4 @ 0x020168e4, 0x38 bytes, Thumb
 * func_020168ac @ 0x020168ac, 0x36 bytes, Thumb
 * func_02016884 @ 0x02016884, 0x26 bytes, Thumb
 */

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    unsigned char unk_10;
    char pad_11[3];
    int unk_14;
} UnkStruct_0201691c;

extern void *func_02083050(int);
extern void *func_02083038(int);
extern void func_0201651c(void *p, int x);
extern int func_0208308c(void *p);
extern void func_02016764(void *p, void *q, int a, int b, int c, int d, int e, int f);
extern void func_02055050(void *p);
extern void func_02055de0(void *p, int callback, int a, int b, void *q, int c);
extern int func_02016618(void *p);
extern void func_020165f4(void *p);
extern void func_0201c6a8(void *self);
extern void *func_02082fec(int, int);
extern void func_0205cc1c(void *, int, int, int);
extern int func_0205cb94(void *);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);
extern int func_0201b380(int arg);
extern int func_0201b37c(int arg);
extern int func_0201b378(int arg);
extern int func_020164a0(int param, int param2);

int func_020169a8(int arg)
{
    func_02083050(arg);
    return arg;
}

int func_02016998(int arg)
{
    func_02083038(arg);
    return arg;
}

int func_0201691c(UnkStruct_0201691c *param0, void *param1, int param2)
{
    func_0201651c(param0, 0);
    param0->unk_14 = param2;

    if (func_0208308c(param0) == 0) {
        return 0;
    }

    func_02016764(param0, param1, 0, 0, 0, 0x1000, 0, 0);
    func_02055050((char *) param1 + 0xec);
    func_02055de0((char *) param1 + 0xec, (int) func_0201c6a8, 6, 1, param1, 0);
    param0->unk_0C = 2;

    if (func_02016618(param0) == 0) {
        func_020165f4(param0);
    }

    param0->unk_10 = 0;
    return 1;
}

int func_020168e4(int p1, int p2, int p3)
{
    void *p;
    int result;
    p = func_02082fec(p1, p3);
    result = 0;
    if (p != 0) {
        func_0205cc1c(p, p2, result, result);
        result = func_02107b44(NNS_G3dGetJntAnmSet(func_0205cb94(p)), 0);
    }
    return result;
}

int func_020168ac(int unused, int selector, int arg)
{
    int result = selector;
    switch (selector) {
        case 0:
            result = func_0201b380(arg);
            break;
        case 1:
            result = func_0201b37c(arg);
            break;
        case 2:
            result = func_0201b378(arg);
            break;
    }
    return result;
}

int func_02016884(int param, int a, int b)
{
    a = func_020168ac(param, a, b);
    b = func_020164a0(param, 0);
    if (a == b) {
        return 1;
    } else {
        return 0;
    }
}
