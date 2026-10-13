/* func_020abb5c @ 0x020abb5c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020abb48(void *param);

void func_020abb5c(void *param)
{
    unsigned char val;
    unsigned char *ptr;

    val = ((unsigned char *) param)[0x141];
    if (val == 0) {
        func_020abb48(param);
    }
}
