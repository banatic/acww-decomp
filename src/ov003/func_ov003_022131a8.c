/* func_ov003_022131a8 @ 0x022131a8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022131a4(void *p, int x);
extern void func_ov003_02213198(void *p, int y);

void func_ov003_022131a8(void *p, unsigned char c, int x, int y)
{
    *(unsigned char *) p = c;
    func_ov003_022131a4(p, x);
    func_ov003_02213198(p, y);
}
