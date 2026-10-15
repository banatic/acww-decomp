/* func_ov045_02260f94 @ 0x02260f94, 0x30 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b790(void *argument0);
extern int func_02055d0c(void *dst, const void *src, int size);
extern void func_ov004_022304bc(void);

int func_ov045_02260f94(void *arg)
{
    if (!func_0201b790(arg)) {
        return 0;
    }

    (void) ((void *) func_02055d0c((char *) arg + 0xec, (char *) arg + 0x65c, 0xe));
    func_ov004_022304bc();
    return 1;
}
