/* func_ov048_022622ec @ 0x022622ec, 0x34 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_02262390(void *param, int a);
extern void func_ov048_02262618(void *param, int a, int b);
extern void func_ov048_022616b8(void *param, int a);

void func_ov048_022622ec(void *arg)
{
    int two = 2;
    char *ptr;
    func_ov048_02262390(arg, 1);
    func_ov048_02262618(arg, two, two);
    ptr = *(char **) ((char *) arg + 0xB8);
    *(short *) (ptr + 0x0E6E) = 200;
    func_ov048_022616b8(arg, 1);
}
