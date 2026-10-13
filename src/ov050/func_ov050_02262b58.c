/* func_ov050_02262b58 @ 0x02262b58, 0x54 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_020154b4(void *, unsigned short *, int, int, int);
extern void func_0209ad9c(int, int);
extern int func_0209b4d4(void);
extern int func_0209bd44(int);
extern int func_0209bc40(int);
extern void func_0209bb90(int, int);

void func_ov050_02262b58(void *a, int b)
{
    unsigned short h = 0x11a8;
    int v;

    func_020154b4(a, &h, 0, 5, 0);
    *(int *) ((char *) a + 0xd0) = 6;
    func_0209ad9c(b, 0);
    v = func_0209b4d4();
    if (func_0209bd44(v) != 0) {
        if (func_0209bc40(v) == 0xb) {
            func_0209bb90(v, 1);
        }
    }
}
