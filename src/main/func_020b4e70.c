/* func_020b4e70 @ 0x020b4e70, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c18(void);
extern void func_020a9334(void *object, void *next);

void func_020b4e70(int object)
{
    int next = func_02050c18();
    func_020a9334((void *) object, (void *) next);
}
