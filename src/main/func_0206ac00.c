/* func_0206ac00 @ 0x0206ac00, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c48(void);
extern void func_020a9334(void *object, void *next);

int func_0206ac00(int object)
{
    register int preserved_result;
    int next = func_02050c48();
    func_020a9334((void *) object, (void *) next);
    asm { mov preserved_result, r0 }
    return preserved_result;
}
