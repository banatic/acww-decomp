/* func_020a0efc @ 0x020a0efc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(int a, int b);
extern int func_02090040(int a);
extern int func_02090124(int);
extern void func_020882f0(void *);
extern int func_020a6ed0(void);
extern void func_020a0c74(int a, int b);
extern int data_020ccf94;

void func_020a0efc(int param)
{
    int i = 3;
    int temp = data_020ccf94;
    do {
        if (func_02073dd4(temp, i) != 0) {
            func_020882f0((void *) func_02090124((int) func_02090040(i)));
        }
    } while (--i >= 0);
    func_020a0c74(param, func_020a6ed0());
}
