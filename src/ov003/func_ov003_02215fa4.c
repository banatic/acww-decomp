/* func_ov003_02215fa4 @ 0x02215fa4, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int, int);
extern void func_02095694(int, int);
extern void func_0200f27c(void *, int);
extern int data_020ccf94;

void func_ov003_02215fa4(int *p)
{
    if (func_02073908(data_020ccf94, p[0x200]) == 0) {
        func_02095694(0, p[0x200]);
        func_0200f27c(p, 0);
    }
}
