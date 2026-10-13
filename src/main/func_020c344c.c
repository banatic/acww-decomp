/* func_020c344c @ 0x020c344c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de8(void *);
extern int func_02019e00(void *);
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, unsigned short, int);
extern unsigned short data_020c80f8;

int func_020c344c(void *p)
{
    if (func_02019de8((char *) p + 0x564) != 0) {
        if (func_02019e00((char *) p + 0x564) == 3) {
            func_02019d0c((char *) p + 0x564, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    return 1;
}
