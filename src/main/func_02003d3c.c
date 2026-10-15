/* func_02003d3c @ 0x02003d3c, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003cc0(int *);
extern int func_020ec39c(void);
extern void func_02003c38(int *);
extern void func_02003bc8(int *);
extern void func_02003bc4(void *receiver);

void func_02003d3c(int *arg0)
{
    int x = func_02003cc0(arg0);
    if (x != 0) {
        int s = func_020ec39c();
        if (s == 1) {
            *arg0 = 2;
        } else if (s == 2) {
            *arg0 = 1;
        } else if (s == 3) {
            *arg0 = 0;
        } else {
            *arg0 = 3;
        }
    }
    func_02003c38(arg0);
    func_02003bc8(arg0);
    func_02003bc4(arg0);
}
