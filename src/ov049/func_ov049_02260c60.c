/* func_ov049_02260c60 @ 0x02260c60, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c2bc(void);
extern void func_ov004_0223b340(int, int);
extern void func_ov049_022610c4(int, int);

void func_ov049_02260c60(int param)
{
    int *ptr;
    int a, b;

    if (func_ov004_0222c2bc() != 0) {
        ptr = *(int **) (param + 0xb0);
        a = *(int *) ((char *) ptr + 0x728);
        b = *(int *) ((char *) ptr + 0x72c);
        func_ov004_0223b340(a, b);
        func_ov049_022610c4(param, 0);
    }
}
