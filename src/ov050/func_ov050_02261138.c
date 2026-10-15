/* func_ov050_02261138 @ 0x02261138, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209a050(void *object);
extern int func_02015330(int *p, short *s, int a, int b, int c);

void func_ov050_02261138(int *p, int flag)
{
    if (flag == 0) {
        int object = p[51];
        if (object >= 0) {
            int a;
            short s;
            func_0209a050((void *) object);
            s = 0x36fc;
            a = 0;
            func_02015330(p, &s, a, 5, a);
        }
        p[52] = 55;
    }
}
