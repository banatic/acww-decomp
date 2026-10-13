/* func_ov050_022640e4 @ 0x022640e4, 0x70 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_022606b4(void *);
extern int func_ov050_022605c0(void *);
extern int func_ov050_02260528(void *);
extern int func_ov050_02260718(void *);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov050_02264834(void *, int);

int func_ov050_022640e4(void *p)
{
    if (func_ov050_022606b4(p)) {
        return 1;
    }
    if (func_ov050_022605c0(p)) {
        return 1;
    }
    if (func_ov050_02260528(p)) {
        return 1;
    }
    if (func_ov050_02260718(p)) {
        return 1;
    }

    if (func_02019e00((char *) p + 0x564) == 10) {
        if (func_02019de8((char *) p + 0x564)) {
            *(unsigned short *) ((char *) p + 0x730) = 24;
            func_ov050_02264834(p, 1);
        }
    }
    return 1;
}
