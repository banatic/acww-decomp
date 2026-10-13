/* func_ov048_02261640 @ 0x02261640, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209fea4(void);
extern void func_ov048_022616b8(int a, int b);

void func_ov048_02261640(int a)
{
    int *p;
    int v;

    if (func_0209fea4() != 0) {
        p = (int *) (a + 0xb4);
        v = *p + 1;
        func_ov048_022616b8(a, v);
    } else {
        p = (int *) (a + 0xb4);
        v = *p + 2;
        func_ov048_022616b8(a, v);
    }
}
