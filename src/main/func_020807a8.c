/* func_020807a8 @ 0x020807a8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807dc(int arg, void *);
extern int func_020807c0(int arg1, int arg2);

int func_020807a8(int arg, void *argument1)
{
    return func_020807c0(arg, func_020807dc(arg, (void *) argument1));
}
