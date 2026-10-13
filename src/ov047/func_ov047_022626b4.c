/* func_ov047_022626b4 @ 0x022626b4, 0x4c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov047_022618cc(void *a, void *b);
extern unsigned short data_020c80f8;

int func_ov047_022626b4(void *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }
    func_0201c280(arg, (char *) arg + 0x658);
    func_ov047_022618cc((char *) arg + 0x658, arg);
    *((unsigned short *) ((char *) arg + 0x730)) = data_020c80f8;
    *((int *) ((char *) arg + 0x73c)) = -1;
    return 1;
}
