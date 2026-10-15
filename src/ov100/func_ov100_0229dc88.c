/* func_ov100_0229dc88 @ 0x0229dc88, 0x50 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov002_02209114(void *, unsigned char, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229dc88(unsigned char *self)
{
    if (func_0208e484(self + 0x2274) == 0) {
        return;
    }
    func_ov002_02209114(self + 0x22d8, self[0x2926], 1);
    self[0x2925] = *(self + self[0x2926] + 0x26c5);
    func_ov002_02208098((void *) (self), 0x12);
}
