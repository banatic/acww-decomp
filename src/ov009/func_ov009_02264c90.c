/* func_ov009_02264c90 @ 0x02264c90, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d1f24[];
extern void func_020b2a68(void *dst, const void *src, int flag);
extern int func_020b2a5c(void *buf);
extern void func_020b2a64(void *buf);

int func_ov009_02264c90(void *param0)
{
    int flag = 0;
    unsigned int val;
    unsigned int index;
    char buffer[16];
    const char *ptr;
    int result;

    val = *(unsigned short *) ((char *) param0 + 0x136);
    if (val >= 0x5000 && val <= 0x5021) {
        flag = 1;
    }

    if (flag) {
        index = val & 0xfff;
    } else {
        index = -1;
    }

    if (index < 0x22) {
        ptr = (const char *) data_020d1f24 + 10 * index;
    } else {
        ptr = (const char *) data_020d1f24;
    }

    func_020b2a68(buffer, ptr, flag);
    result = func_020b2a5c(buffer);
    func_020b2a64(buffer);
    return result;
}
