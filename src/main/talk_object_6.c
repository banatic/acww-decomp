/* talk_object_6: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067718 @ 0x02067718, 0x10 bytes, Thumb
 * func_020676d0 @ 0x020676d0, 0x48 bytes, Thumb
 */

extern void func_020a8c1c(int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0208012c(int, void *, int);

void func_02067718(int p0)
{
    func_020a8c1c((p0 + 7756));
}

int func_020676d0(char *self)
{
    int result;
    int res;
    void *obj;
    int tmp;

    obj = *(void **) (self + 0x14a8);
    result = (*(int (**)(void *))(*(char **) obj + 0x68))(obj);
    res = 0;
    func_020a8c1c((int) (self + 0x1e4c));
    if (result != 0) {
        tmp = func_02099870((int) func_020984e8());
        if (func_0208012c(result, self + 0x1e4c, tmp) != 0) {
            res = 1;
        }
    }
    return res;
}
