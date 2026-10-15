/* func_ov104_0229dad8 @ 0x0229dad8, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a1e8(void);

int func_ov104_0229dad8(void *receiver)
{
    int x;
    x = func_0209a1e8();
    if (x == -1) {
        return 0x21;
    } else {
        return (unsigned char) (x + 0xb);
    }
}
