/* func_ov094_0229a768 @ 0x0229a768, 0x64 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a328(const void *ptr, int id);
extern int func_ov094_0229a524(const void *ptr, int id);
extern int func_02088d9c(int val);
extern int func_02088d94(int val);
extern void func_ov094_0229a668(const void *ptr, int x, int y);

void func_ov094_0229a768(const void *a, int b, int c)
{
    if (func_ov094_0229a328((const char *) a + 0xa40, 0x21)) {
        int tmp = func_ov094_0229a524(a, 0x21);
        int x = b + func_02088d9c(tmp) + 0x80;
        int y = c + func_02088d94(tmp) + 0x60;
        func_ov094_0229a668(a, x, y);
    }
    if (func_ov094_0229a328((const char *) a + 0xa40, 0x22)) {
        c += 0xac;
        func_ov094_0229a668(a, b + 4, c);
    }
}
