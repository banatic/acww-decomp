/* func_020804b8 @ 0x020804b8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int arg, void *);
extern int func_020804e8(int arg);
extern int func_02081e94(int a, int b, int c, int d);

int func_020804b8(int a, int b)
{
    int ret;
    ret = func_020807a8(a, (void *) b);
    if (ret != 0) {
        goto done;
    }
    ret = func_020804e8(a);
    if (ret == 0) {
        goto done;
    }
    func_02081e94(ret, b, 0, 0);
done:
    return ret;
}
