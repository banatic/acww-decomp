/* func_ov104_0229d3ac @ 0x0229d3ac, 0x44 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d8a8(void *p, unsigned char c);
extern int func_ov104_0229c364(void *p, int n);

int func_ov104_0229d3ac(void *p)
{
    int x = func_ov104_0229d8a8(p, ((unsigned char *) p)[0xb8]);
    if (func_ov104_0229c364(p, 0x20)) {
        x += 0x100;
    } else if (func_ov104_0229c364(p, 0x10)) {
        x -= 0x100;
    }
    return x + 8;
}
