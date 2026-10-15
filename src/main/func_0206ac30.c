/* func_0206ac30 @ 0x0206ac30, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c38(void);
extern void func_020a9334(void *object, void *next);

void func_0206ac30(int object)
{
    int next = func_02050c38();
    func_020a9334((void *) object, (void *) next);
}
