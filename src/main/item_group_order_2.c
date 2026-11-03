/* item_group_order_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02064120 @ 0x02064120, 0x2 bytes, Thumb
 * func_0206411c @ 0x0206411c, 0x2 bytes, Thumb
 * func_02064108 @ 0x02064108, 0x12 bytes, Thumb
 * func_020640e0 @ 0x020640e0, 0x28 bytes, Thumb
 */

extern int func_020644cc(int arg);
extern unsigned char data_020cca9c[];

void func_02064120(void *object) {}

void func_0206411c(void *object) {}

void func_02064108(char *ptr)
{
    *ptr = func_020644cc(6);
}

unsigned char *func_020640e0(unsigned char *p)
{
    if (*p >= 6) {
        *p = *p % 6;
    }
    return data_020cca9c + *p * 3;
}
