/* func_ov108_0229cd90 @ 0x0229cd90, 0x28 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220a720(void *p, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0200467c(int cmd);

void func_ov108_0229cd90(void *arg)
{
    func_ov002_0220a720((char *) arg + 0x2a0c, 9);
    func_ov002_02208098((void *) (arg), 23);
    func_0200467c(40);
}
