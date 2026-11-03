/* field_actor_place_states_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b468 @ 0x0222b468, 0x2c bytes, Thumb
 * func_ov004_0222b440 @ 0x0222b440, 0x28 bytes, Thumb
 * func_ov004_0222b42c @ 0x0222b42c, 0x14 bytes, Thumb
 * func_ov004_0222b428 @ 0x0222b428, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b428;

extern void func_ov004_0222b4d4(unsigned char *addr, unsigned char *out);
extern int func_ov004_0222b4e0(unsigned char *addr, unsigned char v, int n, int arg2);
extern int func_02056f94(void *p);
extern int func_ov004_0222bdf0(void *self, int a, int b, int d);
extern void func_02010f5c(void *arg);

void func_ov004_0222b468(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_0222b4d4(base + 0x8f0, &val);
    func_ov004_0222b4e0(base, val, 6, arg2);
}

void func_ov004_0222b440(void *self)
{
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_ov004_0222bdf0(self, 0, 6, ~0);
    }
}

void func_ov004_0222b42c(void *arg)
{
    func_02010f5c(arg);
    func_ov004_0222b440(arg);
}

void func_ov004_0222b428(UnkStruct_0222b428 *p, unsigned char v)
{
    p->unk_00 = v;
}
