/* func_ov106_0229d3e8 @ 0x0229d3e8, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);
extern void *func_ov002_0220a720(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229d3e8(void *self)
{
    func_0200467c(0x27);
    func_ov002_0220a720((char *) self + 0x3fb4, 3);
    func_ov002_02208098((void *) (self), 0x1f);
    ((char *) self)[0xbe] = 0;
}
