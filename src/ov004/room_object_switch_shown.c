/* room_object_switch_shown: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212430 @ 0x02212430, 0x1c bytes, Thumb
 * func_ov004_02212408 @ 0x02212408, 0x28 bytes, Thumb
 * func_ov004_022123ec @ 0x022123ec, 0x1c bytes, Thumb
 * func_ov004_022123c4 @ 0x022123c4, 0x28 bytes, Thumb
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_0220cfec(void *object, unsigned char value);

int func_ov004_02212430(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    return 0x1;
}

void func_ov004_02212408(char *self)
{
    func_ov004_0220d280((void *) ((unsigned char *) self + 0x740), 0, 0);
    func_ov004_0220cfec(self + 0x764, 0);
}

int func_ov004_022123ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    return 0x1;
}

void func_ov004_022123c4(char *self)
{
    func_ov004_0220d280((void *) ((unsigned char *) self + 0x740), (unsigned char) 1, 0);
    func_ov004_0220cfec(self + 0x764, 1);
}
