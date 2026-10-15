/* func_ov048_02261ee4 @ 0x02261ee4, 0x30 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a0194(void);
extern int func_020984e8(void);
extern int func_02099664(int);
extern void func_02077be8(unsigned char *);
extern int func_020a0174(void);
extern void func_ov048_02261e78(int, int);

void func_ov048_02261ee4(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;

    if (r4 == 0) {
        func_020a0194();
        func_02077be8((unsigned char *) func_02099664((int) func_020984e8()));
        func_020a0174();
    }

    func_ov048_02261e78(r5, r4);
}
