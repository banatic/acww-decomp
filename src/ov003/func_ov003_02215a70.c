/* func_ov003_02215a70 @ 0x02215a70, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int, int);
extern void func_02036458(int);
extern void func_0206026c(void *, int);

extern int data_020ccf94;
extern int data_021c526c;

void func_ov003_02215a70(void *param0, int param1)
{
    if (func_02073908(data_020ccf94, *(int *) ((char *) param0 + 0x800)) != 0) {
        func_02036458(data_021c526c + 0x1c4);
        return;
    }
    if (param1 == 0x50) {
        return;
    }
    if (param1 == 0x51) {
        return;
    }
    func_0206026c((char *) param0 + 0x5c8, 1);
}
