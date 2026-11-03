/* field_actor_room_states_17: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222913c @ 0x0222913c, 0x34 bytes, Thumb
 * func_ov004_0222911c @ 0x0222911c, 0x20 bytes, Thumb
 */

extern void func_ov004_022291cc(char *src, int *b, int *c, int *a);
extern int func_ov004_0222920c(char *p, int *b, int *c, int *a, int p5, int p6);
extern void func_020110a0(void *object, short *values);

void func_ov004_0222913c(char *p1, int p2)
{
    int a, b, c;
    func_ov004_022291cc(p1 + 0x8f0, &b, &c, &a);
    func_ov004_0222920c(p1, &b, &c, &a, 6, p2);
}

void func_ov004_0222911c(char *self, int stateId)
{
    const int *src = (const int *) (self + 0x7d4);
    int *dst = (int *) (self + 0x5c);
    dst[0] = src[0];
    dst[2] = src[1];
    func_020110a0(self, (short *) (src + 2));
}
