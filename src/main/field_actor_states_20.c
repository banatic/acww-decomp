/* field_actor_states_20: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c258 @ 0x0200c258, 0x70 bytes, Thumb
 * func_0200c200 @ 0x0200c200, 0x58 bytes, Thumb
 * func_0200c1b8 @ 0x0200c1b8, 0x48 bytes, Thumb
 * func_0200c1a4 @ 0x0200c1a4, 0x14 bytes, Thumb
 * func_0200c198 @ 0x0200c198, 0xc bytes, Thumb
 * func_0200c158 @ 0x0200c158, 0x40 bytes, Thumb
 * func_0200c120 @ 0x0200c120, 0x38 bytes, Thumb
 * func_0200c0dc @ 0x0200c0dc, 0x42 bytes, Thumb
 * func_0200c0d4 @ 0x0200c0d4, 0x6 bytes, Thumb
 * func_0200c0c8 @ 0x0200c0c8, 0xa bytes, Thumb
 */

typedef struct {
    char pad_00[0x13c];
    void *value13c;
    char pad_140[0x170 - 0x140];
    int state170;
} UnkStruct_0200c258;

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0200c258_2;

typedef int (*Fn)(void *);

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_0200c200;

typedef struct UnkStruct_0200c120 {
    char pad_00[0x800];
    unsigned int unk_800;
} UnkStruct_0200c120;

extern void *func_0203dfac(void);
extern void *func_020825e8(void *);
extern int func_0200beb8(void *a, int b, int c);
extern struct {
    unsigned short pad0;
    unsigned short field2;
} data_021fbe40;
extern int data_020ccf94;
extern void func_0200c33c(void *arg);
extern int func_02073908(int a, int b);
extern void func_0200c2c8(void *arg);
extern int func_0201100c(void *arg);
extern void func_02010d64(void *arg);
extern int func_0200f554(void *arg);
extern unsigned int func_0200e92c(int *);
extern void func_0200e90c(int *, int, int, int);
extern int func_0200e894(void *, int *);
extern int func_0200e91c(int *);
extern void func_020109a0(int, int, int, unsigned short);
extern int func_02056f94(char *p);
extern int func_02008258(char *p, int val);
extern int func_0200c9a8(char *p, int a, int b, int c);
extern void func_02010f5c(void *p);

void func_0200c258(UnkStruct_0200c258 *self)
{
    void *ptr = 0;
    int state = self->state170;

    if (state == 2) {
        ptr = self->value13c;
    } else if (state == 1) {
        if (data_021fbe40.field2 & 0x400) {
            ptr = func_0203dfac();
        }
    }

    if (ptr != 0) {
        UnkStruct_0200c258_2 *obj = (UnkStruct_0200c258_2 *) ptr;
        unsigned short local = (unsigned short) obj->unk_08;
        void *res = func_020825e8(&local);
        if (res != 0) {
            Fn fn = *(Fn *) ((char *) *(void **) res + 0xa0);
            int rv = fn(res);
            if (rv != -1) {
                func_0200beb8(self, 5, -1);
            }
        }
    }
}

void func_0200c200(void *arg)
{
    func_0200c33c(arg);
    if (func_02073908(data_020ccf94, ((UnkStruct_0200c200 *) arg)->unk_800) != 0) {
        func_0200c2c8(arg);
        func_0201100c(arg);
        func_02010d64(arg);
        func_0200c258((UnkStruct_0200c258 *) arg);
    } else {
        if (func_0200f554(arg) != 0) {
            func_0201100c(arg);
        }
        func_02010d64(arg);
    }
}

int func_0200c1b8(void *a, int b, int c)
{
    int local[8];
    int result;
    if (*(int *) ((char *) a + 0x704) != 0x12) {
        return 1;
    }
    func_0200e92c(local);
    func_0200e90c(local, 0x13, b, c);
    result = func_0200e894(a, local);
    func_0200e91c(local);
    return result;
}

void func_0200c1a4(int a, void *message, int previous)
{
    func_020109a0(a, 0x84, 3, 0);
}

void func_0200c198(int r0, int r1)
{
    func_0200c1b8((void *) r0, 5, r1);
}

void func_0200c158(char *p)
{
    if (func_02056f94(p + 0x2D0) != 0) {
        *(int *) (p + 0x7FC) = func_02008258(p, *(int *) (p + 0x7F0));
        func_0200c9a8(p, 7, 5, -1);
    }
}

void func_0200c120(UnkStruct_0200c120 *p)
{
    func_02010f5c(p);
    if (func_02073908((*(unsigned int *) &data_020ccf94), p->unk_800) == 0) {
        func_0200f554(p);
    }
    func_02010d64(p);
    func_0200c158((char *) p);
}

int func_0200c0dc(int a, char b, char c, int d, short e)
{
    char buf[28];
    char *p;
    int result;

    func_0200e92c((int *) buf);
    func_0200e90c((int *) buf, 20, d, e);
    p = &buf[12];
    p[1] = b;
    p[0] = c;
    result = func_0200e894((void *) a, (int *) buf);
    func_0200e91c((int *) buf);
    return result;
}

void func_0200c0d4(unsigned char *p0, int p1, int p2)
{
    p0[1] = p1;
    p0[0] = p2;
}

void func_0200c0c8(unsigned char *p, unsigned char *out1, unsigned char *out2)
{
    *out1 = p[1];
    *out2 = p[0];
}
