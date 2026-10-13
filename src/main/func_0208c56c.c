/* func_0208c56c @ 0x0208c56c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d0a70[];
extern int func_020a80c4(int a, int b, int c, int d);
extern void func_0208c3c0(void *);

int func_0208c56c(void *arg)
{
    int i;
    int found = 0;
    for (i = 0; i < 9; i++) {
        unsigned char b0 = data_020d0a70[i * 2];
        const unsigned char *p = &data_020d0a70[i * 2];
        unsigned char b1 = p[1];
        int a = b0 + 0x80;
        int c = b1 + 0x60;
        if (func_020a80c4(a, a + 0x10, c, c + 0x10) != 0) {
            found = 1;
            *(int *) ((char *) arg + 0xc4) = i;
            func_0208c3c0(arg);
            break;
        }
    }
    return found;
}
