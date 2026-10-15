/* func_0201786c @ 0x0201786c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de4(int);
extern int func_02017f1c(void *a, void *b, int c, int d, int e);
extern void func_02019af0(void *a, int b);

void func_0201786c(void *a, void *b)
{
    int c;
    int d;

    c = func_02019de4((int) a);
    d = c + 0x22;
    if (func_02017f1c(a, b, d, 0x28, 1) != 0) {
        func_02019af0(a, 1);
    }
}
