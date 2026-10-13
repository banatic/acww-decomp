/* func_02097d68 @ 0x02097d68, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097d38(const unsigned char *a, int n);
extern void func_02097d50(const unsigned char *a, const int *b);

int func_02097d68(const unsigned char *a, const int *b)
{
    if (func_02097d38(a, 0x80)) {
        if (a[2] == b[0] && a[1] == b[1] && a[0] == b[2]) {
            return 1;
        } else {
            return 0;
        }
    } else {
        func_02097d50(a, b);
        return 1;
    }
}
