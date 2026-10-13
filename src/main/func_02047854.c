/* func_02047854 @ 0x02047854, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020479f0(int a, int b, int c);
extern void func_020b2eb8(void);

int func_02047854(int a, int b, int c, int d)
{
    int result = 0;
    switch (b) {
        case 16:
            result = 1;
            break;
        case 17:
        case 97:
            func_020479f0(a, c, d);
            result = 1;
            break;
        case 98:
            func_020b2eb8();
            result = 1;
            break;
        default:
            break;
    }
    return result;
}
