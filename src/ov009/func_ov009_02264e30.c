/* func_ov009_02264e30 @ 0x02264e30, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d1f24[];
extern void func_020b2a68(void *dst, void *src);
extern int func_020b2a48(void *ptr);
extern void func_020b2a64(void *ptr);

int func_ov009_02264e30(void *p)
{
    unsigned int key;
    int flag = 0;
    unsigned char buffer[16];
    char *ptr;
    int shifted;

    key = *(unsigned short *) ((char *) p + 0x136);
    if (key >= 0x5000 && key <= 0x5021) {
        flag = 1;
    }
    if (flag) {
        key &= 0xfff;
    } else {
        key = -1;
    }
    if (key < 0x22) {
        ptr = data_020d1f24 + key * 10;
    } else {
        ptr = data_020d1f24;
    }
    func_020b2a68(buffer, ptr);
    shifted = func_020b2a48(buffer) << 13;
    func_020b2a64(buffer);
    return shifted;
}
