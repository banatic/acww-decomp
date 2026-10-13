/* func_ov051_02260c44 @ 0x02260c44, 0x50 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a12ac(void);
extern int func_ov051_022605e8(int, int);
extern void func_0206844c(int, char *, int);
extern int data_ov051_022615c0;

void func_ov051_02260c44(int arg0)
{
    char local_8;
    char local_9;

    if (func_020a12ac() != 0) {
        local_8 = (char) func_ov051_022605e8(arg0, 0x25);
        func_0206844c(*(int *) (arg0 + 0x40), &local_8, data_ov051_022615c0);
    } else {
        local_9 = (char) func_ov051_022605e8(arg0, 0x1f);
        func_0206844c(*(int *) (arg0 + 0x40), &local_9, data_ov051_022615c0);
    }
}
