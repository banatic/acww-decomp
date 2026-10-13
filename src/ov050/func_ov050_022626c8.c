/* func_ov050_022626c8 @ 0x022626c8, 0x38 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209ad9c(void *, int);
extern int func_0209b4d4(void);
extern void func_0209bb90(int, int);
extern void func_0209a8fc(void *);

void func_ov050_022626c8(void *a, void *b)
{
    func_0209ad9c(b, 0);
    func_0209bb90(func_0209b4d4(), 2);
    func_0209a8fc(b);
    *(char *) (*(char **) ((char *) a + 0xB4) + 0x73E) = 0;
}
