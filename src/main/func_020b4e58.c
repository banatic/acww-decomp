/* func_020b4e58 @ 0x020b4e58, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c10(void);
extern void func_020a9334(void *object, void *next);

void func_020b4e58(int object)
{
    int next = func_02050c10();
    func_020a9334((void *) object, (void *) next);
}
