/* func_02079478 @ 0x02079478, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6680(void);

void func_02079478(unsigned char *r4)
{
    if (func_020b6680() == 0) {
        r4[0x1d] |= 2;
    }
}
