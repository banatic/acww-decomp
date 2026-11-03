/* field_actor_motion_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02010eb4 @ 0x02010eb4, 0x18 bytes, Thumb
 * func_02010e58 @ 0x02010e58, 0x5c bytes, Thumb
 * func_02010e48 @ 0x02010e48, 0x10 bytes, Thumb
 * func_02010e10 @ 0x02010e10, 0x38 bytes, Thumb
 * func_02010dc8 @ 0x02010dc8, 0x48 bytes, Thumb
 * func_02010d88 @ 0x02010d88, 0x40 bytes, Thumb
 * func_02010d64 @ 0x02010d64, 0x24 bytes, Thumb
 * func_02010d28 @ 0x02010d28, 0x3c bytes, Thumb
 * func_02010ca4 @ 0x02010ca4, 0x84 bytes, Thumb
 */

typedef struct {
    char pad_00[0x6f4];
    int unk_6F4;
    char pad_6F8[4];
    int unk_6FC;
} UnkStruct_02010e10;

typedef struct {
    int x, y, z;
} Vec3;

struct Self5 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x7f0 - 0x68];
    int unk_7F0;
    unsigned char pad_7F4[0x800 - 0x7f4];
    int unk_800;
};

extern unsigned char data_020c798c[];
extern int func_020310c8(int);
extern void func_02089b80(int, int, int, int, int, int, int, int, int, int);
extern void func_02089fc8(char *a);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_020b67ac(void);
extern int func_020b6590(void);
extern void *func_020b7d3c(int h, void *p1, Vec3 *p2, int a3, int a4, int a5, int a6);

int func_02010eb4(int a1, int *a2)
{
    if (data_020c798c[*a2] != 0) {
        return 2;
    } else {
        return 0;
    }
}

void func_02010e58(void *self, int param2, int param3)
{
    int r = func_02010eb4((int) self, (int *) param3);
    func_02089b80((int) ((char *) self + 0x174), (int) self, param2, 0x0fd7, 0x2800, r | 4, 0x2fc, 0x15, (unsigned char) ((unsigned char) (*(unsigned int *) ((char *) self + 0x800))), 0x1000);
}

void func_02010e48(int a, int c)
{
    func_02010e58((void *) a, a + 0x5c, c);
}

void func_02010e10(UnkStruct_02010e10 *p, int arg)
{
    int locals[3];
    locals[0] = p->unk_6F4;
    locals[1] = func_020310c8(0);
    locals[2] = p->unk_6FC;
    func_02010e58(p, (int) locals, arg);
}

void func_02010dc8(int a, int b)
{
    func_02089b80(a + 0x1c4, a, b, 0xfd7, 0x2800, 6, 0x2fc, 0, 0xff, 0x1000);
}

void func_02010d88(int a, int b, int c, int d)
{
    int stack[6];

    stack[0] = d;
    stack[1] = 0x11;
    stack[2] = 0x2c;
    stack[3] = 0;
    stack[4] = 0xff;
    stack[5] = 0x1000;

    func_02089b80(a + 0x1c4, a, b, c, stack[0], stack[1], stack[2], stack[3], stack[4], stack[5]);
}

void func_02010d64(char *p)
{
    func_02010e48((int) p, (int) (p + 0x7f0));
    func_02089fc8(p + 0x174);
}

void func_02010d28(void *param1, void *param2)
{
    func_02010e10((UnkStruct_02010e10 *) param1, (int) ((char *) param1 + 0x7f0));
    func_02089fc8((char *) ((char *) param1 + 0x174));
    func_02010dc8((int) param1, (int) param2);
    func_02089fc8((char *) ((char *) param1 + 0x1c4));
}

int func_02010ca4(struct Self5 *self)
{
    Vec3 *p;
    Vec3 v;
    int h;

    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        int gate = func_020b67ac();
        if (gate == 0) {
            return gate;
        }
        if (self->unk_7F0 != 8) {
            return self->unk_7F0;
        }
    }

    p = (Vec3 *) ((char *) self + 0x5c);
    v.x = self->unk_5C;
    v.y = p->y;
    v.z = p->z;
    v.y = v.y + 0xb33;

    h = func_020b6590();
    return (int) func_020b7d3c(h, (char *) self + 0x214, &v, 0xa00, 0x15cf, 1, (unsigned char) self->unk_800);
}
