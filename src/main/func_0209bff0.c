/* func_0209bff0 @ 0x0209bff0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c38c(int b);
extern void func_020b4a20(void *self, unsigned char *p, void *g);
extern char data_020e35cc;

void func_0209bff0(void *self, int b)
{
    int temp;
    unsigned char v;
    if (func_0209c38c(b)) {
        temp = b;
    } else {
        temp = 7;
    }
    v = (unsigned char) temp;
    func_020b4a20(self, &v, &data_020e35cc);
}
