/* func_0202c934 @ 0x0202c934, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov003_0222f458(void *self, unsigned char idx);
extern int func_0202c99c(int a, int b, int c);
extern int func_020ea990(int a, void *self);

int func_0202c934(void *self, int p2, int p3, int p4, int p5)
{
    unsigned int cond;
    int resultB;
    int i;

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond > 0) {
        for (i = 0; i < 8; i++) {
            int a = func_ov003_0222f458(self, (unsigned char) i);
            resultB = func_0202c99c(a, p2, p3);
            if (resultB == -1) {
                continue;
            }
            if (func_020ea990(p4, self) >= p5) {
                continue;
            }
            return resultB;
        }
    }
    return -1;
}
