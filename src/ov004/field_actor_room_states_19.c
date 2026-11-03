/* field_actor_room_states_19: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022292e8 @ 0x022292e8, 0x28 bytes, Thumb
 * func_ov004_022292c8 @ 0x022292c8, 0x20 bytes, Thumb
 * func_ov004_022292c0 @ 0x022292c0, 0x8 bytes, Thumb
 */

extern int func_02056f94(void *p);
extern int func_ov004_02228dfc(void *self, int a, int b, int d);
extern void func_ov004_02229310(int);
extern int func_0200f554(int);
extern void func_02010d64(int);

void func_ov004_022292e8(void *self)
{
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_ov004_02228dfc(self, 0, 6, ~0);
    }
}

void func_ov004_022292c8(int arg)
{
    func_ov004_02229310(arg);
    func_0200f554(arg);
    func_02010d64(arg);
    func_ov004_022292e8((void *) arg);
}

void func_ov004_022292c0(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
