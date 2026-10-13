/* func_0203a6ec @ 0x0203a6ec, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203a6d4(int);
extern int func_0203a694(int, int);

int func_0203a6ec(int arg)
{
    int i;
    for (i = 0; i < 15U; i++) {
        if (func_0203a6d4(i) == 0x0000fff1) {
            return func_0203a694(i, arg);
        }
    }
    return 0;
}
