/* func_0206de0c @ 0x0206de0c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206dcec(char *);

void func_0206de0c(char *p)
{
    int i;
    func_0206dcec(p);
    func_0206dcec(p + 0x74);
    p += 0xe8;
    for (i = 0; i < 4; i++) {
        func_0206dcec(p + i * 0x74);
    }
}
