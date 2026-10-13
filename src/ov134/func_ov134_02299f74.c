/* func_ov134_02299f74 @ 0x02299f74, 0x5c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002808(int, int, int, int, int);

void func_ov134_02299f74(unsigned char *obj)
{
    if (obj[0xaf]) {
        obj[0xb5] = (unsigned char) ((obj[0xb5] + 0x28) >> 1);
        obj[0xb6] = (unsigned char) ((obj[0xb6] + 0xa8) >> 1);
    } else {
        obj[0xb5] = 0x28;
        obj[0xb6] = 0xa8;
    }
    func_02002808(2, 0, obj[0xb5], 0xff, obj[0xb6]);
}
