/* func_020676d0 @ 0x020676d0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0208012c(int, void *, int);

int func_020676d0(char *self)
{
    int result;
    int res;
    void *obj;
    int tmp;

    obj = *(void **) (self + 0x14a8);
    result = (*(int (**)(void *))(*(char **) obj + 0x68))(obj);
    res = 0;
    func_020a8c1c(self + 0x1e4c);
    if (result != 0) {
        tmp = func_02099870((int) func_020984e8());
        if (func_0208012c(result, self + 0x1e4c, tmp) != 0) {
            res = 1;
        }
    }
    return res;
}
