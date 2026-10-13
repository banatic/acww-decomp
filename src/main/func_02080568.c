/* func_02080568 @ 0x02080568, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02080578(void);
extern void func_020805bc(int param1, void (*param2)(void));

void func_02080568(int arg)
{
    func_020805bc(arg, func_02080578);
}
