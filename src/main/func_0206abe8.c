/* func_0206abe8 @ 0x0206abe8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c50(void);
extern void func_020a9334(void *object, void *next);

void func_0206abe8(int object)
{
    int next = func_02050c50();
    func_020a9334((void *) object, (void *) next);
}
