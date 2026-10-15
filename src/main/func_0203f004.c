/* func_0203f004 @ 0x0203f004, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065c1c(void *a, void *b);
extern void func_02003530(void *a, int b);

extern unsigned char data_021c72cc[];

void func_0203f004(void *r0, int r1)
{
    void *r5 = r0;
    int r4 = r1;

    if (r4 == 2) {
        func_02065c1c((void *) data_021c72cc, (char *) r5 + 0xd4);
    }
    func_02003530(r5, r4);
}
