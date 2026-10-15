/* func_ov004_0220c380 @ 0x0220c380, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220c0c8(void *self);
extern int func_020b6590(void);
extern int func_020b7e04(int value, void *addr);

int func_ov004_0220c380(void *self)
{
    func_ov004_0220c0c8(self);
    func_020b7e04(func_020b6590(), (char *) self + 0x1d4);
    return 1;
}
