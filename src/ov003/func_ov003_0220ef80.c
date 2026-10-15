/* func_ov003_0220ef80 @ 0x0220ef80, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020110a0(void *object, short *values);
extern void func_0200f268(void *self, int a);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern int func_0200f328(void *self, int a);

void func_ov003_0220ef80(void *self, void *message, int previous)
{
    short loc;

    *((char *) self + 0x7d4) = 0;
    loc = -32768;
    func_020110a0((void *) (self), (short *) (&loc));
    func_0200f268(self, 0);
    func_020109a0(self, 0x6a, 0, 0);
    func_0200f328(self, 0x818);
}
