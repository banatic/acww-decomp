/* func_020b7f24 @ 0x020b7f24, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f844(void *, void *);
extern int func_020b7f04(unsigned int, void *, unsigned int, unsigned int, unsigned char);

void func_020b7f24(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned char e)
{
    unsigned char local[12];
    func_0203f844(local, (void *) b);
    func_020b7f04(a, local, c, d, e);
}
