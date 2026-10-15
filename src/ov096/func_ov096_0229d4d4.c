/* func_ov096_0229d4d4 @ 0x0229d4d4, 0x1c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229d508(void *p, int n);
extern void func_ov096_0229fb9c(void *p);

void func_ov096_0229d4d4(void *p)
{
    func_ov096_0229d508(p, ((unsigned char *) p)[0xbb] - 0x1c);
    func_ov096_0229fb9c(p);
}
