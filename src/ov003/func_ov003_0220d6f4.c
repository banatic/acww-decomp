/* func_ov003_0220d6f4 @ 0x0220d6f4, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *ptr);
extern int func_02008258(void *ptr, int value);
extern int func_0200d4e8(void *ptr, int a, int b, int c);
extern int func_02073908(void *ptr, int value);
extern int func_ov003_0220d268(void *ptr);
extern void *data_020ccf94;

void func_ov003_0220d6f4(void *arg)
{
    if (func_02056f94((char *) arg + 0x2d0) != 0) {
        *(int *) ((char *) arg + 0x7fc) = func_02008258(arg, *(int *) ((char *) arg + 0x7f0));
        func_0200d4e8(arg, 3, 1, -1);
    }
    if (func_02073908(data_020ccf94, *(int *) ((char *) arg + 0x800)) != 0) {
        if (((*(unsigned int *) ((char *) arg + 0x2d8) << 4) >> 16) >= 0x18) {
            func_ov003_0220d268(arg);
        }
    }
}
