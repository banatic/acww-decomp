/* func_ov133_0229adc4 @ 0x0229adc4, 0x58 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov133_0229c79c[];
extern int data_ov133_0229c814[];
extern void func_0206fdd4(char *fmt, char *a, int b, char *c, int d, int e);
extern void func_ov133_0229ad78(char *self, int a);

void func_ov133_0229adc4(char *self, int p1, int p2)
{
    int idx = p1 % 3;
    char *p = data_ov133_0229c79c[idx];
    char *q;
    int v;

    if (idx == 0) {
        q = p + 4;
    } else {
        q = p + 3;
    }

    v = data_ov133_0229c814[p1];
    func_0206fdd4(self + 0x394, p, v, q, v + 1, p2);
    func_ov133_0229ad78(self, 2);
}
