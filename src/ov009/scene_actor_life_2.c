/* scene_actor_life_2: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264e30 @ 0x02264e30, 0x68 bytes, Thumb
 * func_ov009_02264dc8 @ 0x02264dc8, 0x68 bytes, Thumb
 * func_ov009_02264d60 @ 0x02264d60, 0x68 bytes, Thumb
 */

extern char data_020d1f24[];
extern void func_020b2a68(void *dst, void *src);
extern int func_020b2a48(void *ptr);
extern void func_020b2a64(void *ptr);
extern int func_020b2a40(void *);
extern int func_020b2a44(void *buf);

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
        ptr = ((unsigned char *) data_020d1f24) + index * 10;
    } else {
        ptr = ((unsigned char *) data_020d1f24);
    }
    func_020b2a68(local, ptr);
    shifted = func_020b2a40(local) << 13;
    func_020b2a64(local);
    return shifted;
}

int func_ov009_02264d60(const void *p)
{
    unsigned char buf[16];
    unsigned int v;
    int flag;
    const unsigned char *table;
    int result;

    flag = 0;
    v = *(const unsigned short *) ((const unsigned char *) p + 0x136);
    if (v >= 0x5000 && v <= 0x5021) {
        flag = 1;
    }
    if (flag != 0) {
        v &= 0xfff;
    } else {
        v = -1;
    }
    if (v < 0x22) {
        table = ((const unsigned char *) data_020d1f24) + v * 10;
    } else {
        table = ((const unsigned char *) data_020d1f24);
    }
    func_020b2a68(buf, (void *) table);
    result = func_020b2a44(buf) << 13;
    func_020b2a64(buf);
    return result;
}
