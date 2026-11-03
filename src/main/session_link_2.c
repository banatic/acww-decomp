/* session_link_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02074308 @ 0x02074308, 0x28 bytes, Thumb
 * func_020742fc @ 0x020742fc, 0xc bytes, Thumb
 * func_020742b4 @ 0x020742b4, 0x48 bytes, Thumb
 * func_02074294 @ 0x02074294, 0x20 bytes, Thumb
 * func_0207428c @ 0x0207428c, 0x8 bytes, Thumb
 * func_02074228 @ 0x02074228, 0x64 bytes, Thumb
 * func_0207417c @ 0x0207417c, 0xac bytes, Thumb
 */

struct UnkStruct_020742b4 {
    char pad_00[0x64];
    volatile int unk_64;
};

struct UnkStruct_0207417c {
    unsigned char pad_00[0x64];
    int unk_64;
};

extern void *data_020ccf94;
int func_02073e30(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020b65c4(void);
extern void func_02073d74(struct UnkStruct_020742b4 *, int);
extern void func_02073de0(struct UnkStruct_020742b4 *, int, int);
extern void func_020a6c8c(void);
extern void func_020a7394(int, int, int, int, int);
extern void func_020a6c7c(void);
extern int func_02073bf4(int, int, int);
extern unsigned int func_02073044(void);
extern int func_020ec338(unsigned short, int, int);
extern int func_02073dd4(void *a, int b);
extern void func_020a6f74(int a, int b);
extern void *func_02073d28(void *a, int b);
extern void func_02077b3c(void *a, int b, int c);
extern int func_02073918(void *a, int b);
extern void func_02073820(void *a);
extern void func_020737f0(void *a, void *b, int c);
extern void func_02073770(void *a, int b, int c);

void func_02074228(unsigned int arg1);

int func_02074308(void)
{
    return func_02073e30(data_020ccf94, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void func_020742fc(void)
{
    func_02074228(0);
}

void func_020742b4(void)
{
    struct UnkStruct_020742b4 *obj;
    int ret;

    obj = (*(struct UnkStruct_020742b4 * *) &data_020ccf94);
    func_02073d74(obj, 2);
    obj->unk_64 = 0;
    func_02073de0(obj, obj->unk_64, 1);
    func_02074228(0);
    func_020a6c8c();
    ret = func_020b65c4();
    func_020a7394(0, ret, 1, 0, 7);
}

void func_02074294(void *arg)
{
    func_02073d74((struct UnkStruct_020742b4 *) data_020ccf94, 0);
    func_02074228((unsigned int) arg);
}

void func_0207428c(void)
{
    func_020a6c7c();
}

void func_02074228(unsigned int arg1)
{
    int i = 3;
    int a = (*(int *) &data_020ccf94);
    do {
        if (i < arg1) {
            int t = func_02073bf4(a, i, 0);
            func_02073044();
            func_020ec338((unsigned short) i, t, 0x1000);
        } else if (i > arg1) {
            int t = func_02073bf4(a, i - 1, 0);
            func_02073044();
            func_020ec338((unsigned short) i, t, 0x1000);
        }
        i--;
    } while (i >= 0);
}

int func_0207417c(int param)
{
    char byte;
    struct UnkStruct_0207417c *self;
    int field;
    struct UnkStruct_0207417c *g2;
    void *p1;
    void *p2;
    struct UnkStruct_0207417c *g3;

    self = (*(struct UnkStruct_0207417c * *) &data_020ccf94);
    field = self->unk_64;

    if (func_02073dd4(self, field) == 0) {
        func_020a6f74(3, 4);
        g2 = (*(struct UnkStruct_0207417c * *) &data_020ccf94);
        p1 = func_02073d28(g2, 4);
        func_02077b3c(p1, 0, 5);
        ((char *) p1)[1] = 0;
        p2 = func_02073d28(g2, 4);
        return func_02073e30(g2, (int) p2, 2, 1, 0, 0, 0, 0, 0, 0);
    } else {
        if (func_02073918(self, 0) != 0) {
            func_020a6f74(field, param);
        } else {
            func_020a6f74(field, 4);
            byte = (char) param;
            g3 = (*(struct UnkStruct_0207417c * *) &data_020ccf94);
            func_02073820(g3);
            func_020737f0(g3, &byte, 1);
            func_02073770(g3, 0, 0);
        }
    }
    return 1;
}
