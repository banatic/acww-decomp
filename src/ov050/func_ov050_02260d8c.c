/* func_ov050_02260d8c @ 0x02260d8c, 0x48 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern int func_ov050_02260718(void *);
extern int data_ov050_022650a8[];

int func_ov050_02260d8c(void *p)
{
    if (*(int *) ((char *) p + 0x64) < *(int *) (data_ov050_022650a8 + 2)) {
        return 0;
    }
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) != 0) {
        goto ret0;
    }
    if (func_ov050_02260718(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
