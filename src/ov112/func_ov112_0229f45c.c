/* func_ov112_0229f45c @ 0x0229f45c, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208090(void *object, unsigned char value);
extern void *func_ov002_0220a720(char *object, int value);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);

void func_ov112_0229f45c(void *a, unsigned char b, int c)
{
    func_ov002_02208090(a, b);
    func_ov002_0220a720((char *) a + 0x427c, c);
    func_ov002_02208098(a, 0x15);
}
