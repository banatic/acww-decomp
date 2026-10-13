/* func_020645e0 @ 0x020645e0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206461c(unsigned char *p);
extern int func_020e92d0(char *addr, int arg);
extern char data_021cb5a0;

int func_020645e0(unsigned char *p)
{
    if (p[0] != 0) {
        goto handle0;
    }
    if (p[1] != 0) {
        goto handle1;
    }
    func_0206461c(p);
    p[0] = (unsigned char) (func_020e92d0(&data_021cb5a0, 0x5a) + 0x1e);
    goto common_exit;
handle1:
    p[1]--;
    return 1;
handle0:
    p[0]--;
common_exit:
    return 0;
}
