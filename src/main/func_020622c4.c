/* func_020622c4 @ 0x020622c4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *ptr);
extern unsigned char *func_0206e7bc(void *ptr, unsigned int val);
extern char data_021cb5e0;

unsigned char func_020622c4(unsigned short *param)
{
    unsigned int mask;
    void *tmp;
    unsigned char *res;

    mask = *param & 0x0fff;
    if (mask >= 0x056e) {
        mask = 0x056d;
    }
    tmp = func_0206e6e8(&data_021cb5e0);
    res = func_0206e7bc(tmp, mask);
    if (res) {
        return *res;
    }
    return 0;
}
