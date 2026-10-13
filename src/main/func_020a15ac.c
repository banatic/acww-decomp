/* func_020a15ac @ 0x020a15ac, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984d4(int, int, int, int);
extern int func_02098844(char *, int);
extern void *func_02099664(int);
extern int func_02077bb8(void *);
extern int func_020508fc(void *, int, int);
extern void func_02077bc0(void *, int);
extern int func_02050af8(char *, char *, void *, int);

extern char data_021dc7bc[];
extern char data_021dc7a8[];
extern char data_021c8188[];
extern char *data_020d1c20[2];

int func_020a15ac(int a, int b, int c, int d)
{
    int t1 = func_020984d4(a, b, c, d);
    int t2 = func_02098844(data_021dc7bc, t1);
    void *ptr = func_02099664(t2);
    int x = func_02077bb8(ptr);
    int y = func_020508fc(ptr, 0x50, x);
    func_02077bc0(ptr, y);
    {
        int off = (char *) ptr - data_021dc7a8;
        if (func_02050af8(data_021c8188, data_020d1c20[0] + off, ptr, 0x50) == 1) {
            return 1;
        }
        if (func_02050af8(data_021c8188, data_020d1c20[1] + off, ptr, 0x50) == 1) {
            return 1;
        }
        return 0;
    }
}
