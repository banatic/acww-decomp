/* text_label: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207096c @ 0x0207096c, 0xc bytes, Thumb
 * func_02070960 @ 0x02070960, 0xc bytes, Thumb
 * func_0207094c @ 0x0207094c, 0x14 bytes, Thumb
 * func_02070934 @ 0x02070934, 0x18 bytes, Thumb
 * func_02070918 @ 0x02070918, 0x1a bytes, Thumb
 * func_020708e4 @ 0x020708e4, 0x34 bytes, Thumb
 * func_020708b4 @ 0x020708b4, 0x2e bytes, Thumb
 * func_02070870 @ 0x02070870, 0x42 bytes, Thumb
 * func_02070854 @ 0x02070854, 0x1a bytes, Thumb
 * func_020707e8 @ 0x020707e8, 0x6a bytes, Thumb
 * func_020707d0 @ 0x020707d0, 0x18 bytes, Thumb
 * func_020707b8 @ 0x020707b8, 0x18 bytes, Thumb
 * func_02070798 @ 0x02070798, 0x20 bytes, Thumb
 * func_02070794 @ 0x02070794, 0x4 bytes, Thumb
 * func_02070790 @ 0x02070790, 0x4 bytes, Thumb
 * func_02070784 @ 0x02070784, 0xc bytes, Thumb
 */

typedef struct {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02070854;

struct UnkStruct_020707e8 {
    unsigned char pad_00[2];
    unsigned short data[41];
};

struct StackLocal {
    unsigned char pad_00[0xc];
    struct UnkStruct_020707e8 inner;
};

typedef struct {
    void *unk_00;
} UnkStruct_020707b8;

struct UnkStruct_02070798 {
    void *unk_00;
};

extern int func_020a8f88(void *ptr);
extern int func_020b4980(int a, int b, int c);
extern int func_020b4a20(int a, char *b, char *c);
extern int func_020b45d0(int a1, int a2, int a3, int a4, int a5, unsigned char a6);
extern void func_020a8874(void *, void *, void *);
extern int func_020a8a70(void *, void *, int, int);
extern int func_020a87e0(void *, void *);
extern int func_0205182c(void *, void *, int);
extern void func_02051608(int a0, int a1, int a2, int a3, int a4);
extern int func_02051ca8(const unsigned short *, unsigned short);
extern void *func_020a88ec(void *p);
extern void *func_020a887c(void *);
extern void *data_020e1784[];
void func_020edb3c(struct UnkStruct_02070798 *self);
extern int func_02051c8c_unk(int a, int b);

void *func_020707d0(void *p);
void *func_020707b8(void *obj);

int func_0207096c(void *ptr)
{
    return func_020a8f88((char *) ptr + 0x12);
}

int func_02070960(int a, int b)
{
    return func_020b4980(a, b, 0);
}

int func_0207094c(int a, char b)
{
    char temp = b;
    return func_02070960(a, (int) (&temp));
}

void func_02070934(int a, char *b, char c)
{
    char temp;
    temp = c;
    func_020b4a20(a, &temp, b);
}

int func_02070918(int a1, int a2, int a3, int a4, int a5, unsigned char a6)
{
    return func_020b45d0(a1, a2, a3, a4, a5, a6);
}

void func_020708e4(void *param1, void *param2, void *param3)
{
    char buffer[0x60];
    func_020707d0(buffer);
    func_020a8874(buffer, param2, param3);
    func_020a8a70(param1, buffer, 0, 0);
    func_020707b8(buffer);
}

void func_020708b4(void *param0, void *param1)
{
    char buffer[0x64];
    func_020707d0(buffer);
    func_020a87e0(buffer, param0);
    func_0205182c(buffer, param1, 0x29);
    func_020707b8(buffer);
}

void func_02070870(int a, int b, int c, int d, unsigned char e)
{
    char buffer[0x64];
    if (d == 0) {
        e = 0;
    }
    func_020707d0((void *) buffer);
    func_020a8874((void *) buffer, (void *) b, (void *) c);
    func_020a8a70((void *) a, (void *) buffer, d, (unsigned char) e);
    func_020707b8((void *) buffer);
}

void func_02070854(UnkStruct_02070854 *obj, int a1, int a2, int a3, int a4)
{
    if (obj->unk_68 != 0) {
        func_02051608(obj->unk_68, a1, a2, a3, a4);
    }
}

int func_020707e8(int arg0, const unsigned short *arg1, unsigned short arg2)
{
    struct StackLocal s;
    int len;
    int i;

    func_020707d0((void *) (&s));
    func_020a87e0((void *) (&s), (void *) arg0);

    len = func_02051ca8(arg1, arg2);
    if (len != func_02051ca8(s.inner.data, arg2)) {
        func_020707b8((void *) (&s));
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (arg1[i] != s.inner.data[i]) {
            func_020707b8((void *) (&s));
            return 0;
        }
    }

    func_020707b8((void *) (&s));
    return 1;
}

void *func_020707d0(void *p)
{
    func_020a88ec(p);
    *(void **) p = ((char *) data_020e1784);
    return p;
}

void *func_020707b8(void *obj)
{
    UnkStruct_020707b8 *o;
    o = (UnkStruct_020707b8 *) obj;
    o->unk_00 = (void *) ((int *) data_020e1784);
    func_020a887c(obj);
    return obj;
}

struct UnkStruct_02070798 *func_02070798(struct UnkStruct_02070798 *self)
{
    self->unk_00 = data_020e1784;
    func_020a887c((void *) self);
    func_020edb3c(self);
    return self;
}

int func_02070794(void)
{
    return 41;
}

int func_02070790(int p0)
{
    return ((int) (p0) + (14));
}

int func_02070784(int arg0)
{
    return func_02051c8c_unk(arg0 + 14, 0x29);
}
