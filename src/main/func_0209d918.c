/* func_0209d918 @ 0x0209d918, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d988(unsigned char *p, int bit);
extern int func_0209d938(void *param);

void func_0209d918(unsigned char *p0, int p1)
{
    unsigned char buf[4];
    buf[0] = p0[0];
    func_0209d988(buf, p1);
    func_0209d938(buf);
}
