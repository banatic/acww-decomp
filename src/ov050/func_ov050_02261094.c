/* func_ov050_02261094 @ 0x02261094, 0x1c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov050_022618d0(void *, int, int);

void func_ov050_02261094(void *p, int a)
{
    if (a != 4) {
        func_ov050_022618d0(p, 0, a);
        *(int *) ((char *) p + 0xD0) = 0x48;
    }
}
