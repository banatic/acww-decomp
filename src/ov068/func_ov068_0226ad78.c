/* func_ov068_0226ad78 @ 0x0226ad78, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201cc6c(void *, int, int);
extern void func_0201cc48(void *);

void func_ov068_0226ad78(int unused, void *ptr, int x, int y, unsigned char flag)
{
    func_0201cc6c((char *) ptr + 0x83c, x, y);
    if (flag) {
        func_0201cc48((char *) ptr + 0x83c);
    }
}
