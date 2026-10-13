/* func_0207d540 @ 0x0207d540, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern int func_02003704(void);
extern int func_020951bc(int);
extern int func_020807a8(int, int);
extern void func_020818c0(void);

void func_0207d540(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    int temp;

    func_0208150c();
    temp = func_02003704();
    if (temp != 0) {
        if (func_020951bc(r4) != 0) {
            if (func_020807a8(r5, r4) != 0) {
                func_020818c0();
            }
        }
    }
}
