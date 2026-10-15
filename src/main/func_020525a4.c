/* func_020525a4 @ 0x020525a4, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern unsigned char data_020e54a8;

extern int func_02073d90(unsigned int);
extern int func_02073918(unsigned int, int);
extern int func_020526b8(int, int, int, int, unsigned char, unsigned char, unsigned char);
extern int func_ov004_0223cd50(void);
extern unsigned char *func_ov004_0223cc10(int, int, int, int);
extern int func_02052794(int, int, int, int, unsigned char, unsigned char, unsigned char);

int func_020525a4(int a, int b, int c, int d, unsigned char e, unsigned char f, unsigned char g)
{
    unsigned int saved;
    unsigned int cond;
    unsigned char *ret;

    saved = data_020ccf94;
    if (func_02073d90(saved) == 0) {
        goto first;
    }
    if (func_02073918(saved, 0) == 0) {
        goto later;
    }
first:
    return func_020526b8(a, b, c, d, e, f, g);

later:
    cond = (data_020e54a8 == 1) ? 1 : 0;
    if (cond == 0) {
        return 0;
    }

    ret = func_ov004_0223cc10(func_ov004_0223cd50(), a, b, c);
    if (ret == 0) {
        return 0;
    }

    if (g != 0) {
        if (func_02052794(a, b, c, d, e, f, 0) != 0) {
            ret[0x77d] = 1;
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}
