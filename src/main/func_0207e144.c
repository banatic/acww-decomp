/* func_0207e144 @ 0x0207e144, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(int *p);

int func_0207e144(void)
{
    int a[3];
    a[0] = 0;
    a[1] = 0;
    func_0209e474(a);
    if (((unsigned char *) a)[4] >= 9 && ((unsigned char *) a)[4] <= 11) {
        return 1;
    }
    return 0;
}
