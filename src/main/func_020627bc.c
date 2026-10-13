/* func_020627bc @ 0x020627bc, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *addr);
extern void *func_0206e7bc(void *p, unsigned int flags);

extern unsigned char data_021cb5e0[];

int func_020627bc(unsigned short *ptr)
{
    int key = 0;
    unsigned int v = *ptr;
    unsigned int flags;
    int ret;
    void *p;
    void *q;

    if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
        key = 1;
    }

    if (key != 0) {
        if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
            key = v - 0x1000;
        } else {
            key = -1;
        }
        key |= 3;
        if ((unsigned int) key < 0x100) {
            key = (unsigned short) (key + 0x1000);
        } else {
            key = 0x1000;
        }
        {
            volatile unsigned short temp = (unsigned short) key;
            flags = temp & 0x0fff;
        }
        if (flags >= 0x056e) {
            flags = 0x056d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, flags);
        if (q) {
            ret = ((unsigned char *) q)[6];
        } else {
            ret = 0;
        }
    } else {
        flags = v & 0x0fff;
        if (flags >= 0x056e) {
            flags = 0x056d;
        }
        p = func_0206e6ec((void *) data_021cb5e0);
        q = func_0206e7bc(p, flags);
        if (q) {
            ret = ((unsigned char *) q)[6];
        } else {
            ret = 0;
        }
    }
    return ret;
}
