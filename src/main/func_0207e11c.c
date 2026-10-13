/* func_0207e11c @ 0x0207e11c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);

int func_0207e11c(void)
{
    int local[2];
    unsigned char b;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    b = ((unsigned char *) local)[4];
    if (b >= 6 && b <= 8) {
        return 1;
    } else {
        return 0;
    }
}
