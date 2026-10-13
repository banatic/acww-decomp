/* func_020412a0 @ 0x020412a0, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);

int func_020412a0(void)
{
    int key = func_020b65c4();
    switch (key) {
        case 6:
        case 12:
        case 13:
        case 14:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
            return 1;
        default:
            return 0;
    }
}
