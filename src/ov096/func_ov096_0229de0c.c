/* func_ov096_0229de0c @ 0x0229de0c, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f290(void *p, unsigned char b);
extern int func_ov096_0229c2fc(void *p, int n);

int func_ov096_0229de0c(void *p)
{
    int val = func_ov096_0229f290(p, ((unsigned char *) p)[0xb5]);
    if (func_ov096_0229c2fc(p, 0x20) != 0) {
        val += 0x100;
    } else if (func_ov096_0229c2fc(p, 0x10) != 0) {
        val -= 0x100;
    }
    val += 8;
    return val;
}
