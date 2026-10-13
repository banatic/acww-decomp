/* func_0207fb70 @ 0x0207fb70, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_0203a6ec(unsigned short);

int func_0207fb70(unsigned short *arg)
{
    if (func_020644cc(2) == 0) {
        if (func_0203a6ec(*arg) == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}
