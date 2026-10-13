/* func_02080af0 @ 0x02080af0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02082164(void *);
extern void func_020a8c1c(void *);
extern int func_0207dd84(void *);
extern int func_020644cc(int);
extern void func_020b4a20(void *, char *, int *);
extern void func_02080ac8(void *, void *);
extern void func_020a8a70(void *, void *, int, int);
extern void func_0208214c(void *);
extern int data_020e1968[];

void func_02080af0(void *arg0, void *arg1, int arg2)
{
    char c;
    int local[7];

    func_02082164(local);
    func_020a8c1c(arg1);
    if (arg2 != 0 && func_0207dd84(arg0)) {
        c = (char) func_020644cc(0x10);
        func_020b4a20(arg1, &c, data_020e1968);
    } else {
        func_02080ac8(arg0, local);
        func_020a8a70(arg1, local, 0, 0);
    }
    func_0208214c(local);
}
