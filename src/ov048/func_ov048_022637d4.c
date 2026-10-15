/* func_ov048_022637d4 @ 0x022637d4, 0x78 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *ptr);
extern void func_0201c280(void *a, void *b);
extern void func_ov048_02262680(void *a, void *b);
extern void func_0201c3f4(void *a, int b);
extern void func_0201b388(void *a, int b);
extern void func_0201b38c(void *a, int b);
extern int func_020b65c4(void);

int func_ov048_022637d4(void *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }

    func_0201c280(arg, (char *) arg + 0x658);
    func_ov048_02262680((char *) arg + 0x658, arg);
    func_0201c3f4(arg, 0x100);
    func_0201b388((char *) arg + 0x2a0, 0xd9);
    func_0201b38c((char *) arg + 0x2a0, 0xd8);

    if (func_020b65c4() != 0xb) {
        *((char *) arg + 0x563) = 1;
    }

    if (func_020b65c4() == 0xc) {
        *((char *) arg + 0x510) = 0;
    }

    return 1;
}
