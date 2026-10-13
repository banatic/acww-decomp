/* func_02023010 @ 0x02023010, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02023010(unsigned int v)
{
    int r = 0;
    switch (v) {
        case 0:
        case 2:
        case 4:
            r = 0;
            break;
        case 5:
        case 6:
            r = 1;
            break;
        case 1:
        case 3:
            r = 2;
            break;
    }
    return r;
}
