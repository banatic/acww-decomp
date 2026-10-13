/* func_020c3c94 @ 0x020c3c94, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_020c3dac(void *, int);

int func_020c3c94(void *param)
{
    if (func_02019e00((char *) param + 0x564) == 3) {
        if (func_02019de8((char *) param + 0x564) == 1) {
            func_020c3dac(param, 0);
        }
    }
    return 1;
}
