/* func_ov003_02215544 @ 0x02215544, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215614(void *p, void *q);
extern void *func_ov003_02215624(void *p, unsigned char c, int n, void *q);

void func_ov003_02215544(void *p, void *q)
{
    unsigned char c;
    func_ov003_02215614((char *) p + 0x8f0, &c);
    func_ov003_02215624(p, c, 6, q);
}
