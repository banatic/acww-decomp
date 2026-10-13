/* func_ov009_02264dc8 @ 0x02264dc8, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1f24[];
extern void func_020b2a68(void *, void *);
extern int func_020b2a40(void *);
extern void func_020b2a64(void *);

int func_ov009_02264dc8(void *obj)
{
    unsigned char local[16];
    unsigned short val;
    unsigned int index;
    int flag = 0;
    unsigned char *ptr;
    int shifted;

    val = *(unsigned short *) ((unsigned char *) obj + 0x136);
    if (val >= 0x5000 && val <= 0x5021) {
        flag = 1;
    }
    if (flag) {
        index = val & 0xfff;
    } else {
        index = -1;
    }
    if (index < 0x22) {
        ptr = data_020d1f24 + index * 10;
    } else {
        ptr = data_020d1f24;
    }
    func_020b2a68(local, ptr);
    shifted = func_020b2a40(local) << 13;
    func_020b2a64(local);
    return shifted;
}
