/* func_0202c3f0 @ 0x0202c3f0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov003_0222d77c(void);
int func_0202c3f0(void *self)
{
    unsigned int ok;
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0 && func_ov003_0222d77c() != 0) {
        return 1;
    }
    return 0;
}
