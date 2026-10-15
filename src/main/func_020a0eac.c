/* func_020a0eac @ 0x020a0eac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073dd4(void *p, int i);
extern int func_02090040(int i);
extern int func_02090124(int);
extern void func_020882f0(void *);
extern void func_020a0c74(void *a, int i);
void func_020a0eac(void *a0)
{
    void *p;
    int i;
    for (i = 3, p = data_020ccf94; i >= 0; i--) {
        if (func_02073dd4(p, i)) {
            func_020882f0((void *) func_02090124((int) func_02090040(i)));
        }
    }
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(p, i)) {
            func_020a0c74(a0, i);
        }
    }
}
