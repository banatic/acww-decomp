/* func_ov050_02263d44 @ 0x02263d44, 0x38 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov050_02264834(void *, int);
extern int func_ov050_02260718(void *);

int func_ov050_02263d44(void *param)
{
    if (func_02019e00((char *) param + 0x564) == 3) {
        if (func_02019de8((char *) param + 0x564) != 0) {
            func_ov050_02264834(param, 0xd);
        } else {
            func_ov050_02260718(param);
        }
    }
    return 1;
}
