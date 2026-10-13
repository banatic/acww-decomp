/* func_0207fb98 @ 0x0207fb98, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0203a6ec(unsigned short);

int func_0207fb98(unsigned short *p)
{
    int r;
    r = func_0203a6ec(*p);
    if (r != 0) {
        return 1;
    } else {
        return 0;
    }
}
