/* func_ov009_02264c40 @ 0x02264c40, 0x22 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *);

int func_ov009_02264c40(void *self)
{
    unsigned char data[4];
    func_0209def4(data);
    if (data[1] >= 6 && data[1] < 18) {
        return 0;
    }
    return 1;
}
