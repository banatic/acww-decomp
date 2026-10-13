/* func_ov087_022791bc @ 0x022791bc, 0x30 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov087_02278fa0(void *, void *);

int func_ov087_022791bc(void *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }
    func_0201c280(arg, (char *) arg + 0x658);
    func_ov087_02278fa0((char *) arg + 0x658, arg);
    return 1;
}
