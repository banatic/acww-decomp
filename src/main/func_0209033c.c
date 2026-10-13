/* func_0209033c @ 0x0209033c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090360(char *p);

void func_0209033c(char *p)
{
    int i;
    for (i = 0; i < 10; i++) {
        func_02090360(p);
        p += 8;
    }
}
