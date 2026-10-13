/* func_02095de0 @ 0x02095de0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *func_02096718(int);
extern int func_0200e828(void *);

int func_02095de0(void)
{
    void *res = func_02096718(4);
    int lim;
    if (res != 0) {
        lim = 6;
        if (lim <= func_0200e828(res)) {
            return 0;
        }
        return 1;
    }
    return 0;
}
