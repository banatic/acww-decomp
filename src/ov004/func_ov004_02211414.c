/* func_ov004_02211414 @ 0x02211414, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02211444(void);
extern void func_02064db8(int a, int b, int c);
extern int func_020b65c4(void);
extern void func_02052038(int a, int b);

void func_ov004_02211414(int a)
{
    int t = func_ov004_02211444();
    if (a == 2) {
        func_02064db8(0, 8, t);
    } else {
        func_02064db8(0, 0xc, t);
    }
    func_02052038(func_020b65c4(), 1);
}
