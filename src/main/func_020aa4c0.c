/* func_020aa4c0 @ 0x020aa4c0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac1e8(void *);
extern int func_020ab270(void *);
extern void func_020ac11c(void *, int, int);

void func_020aa4c0(void *param)
{
    int result;
    void *ptr;
    int flag;

    *(int *) ((char *) param + 8) = 2;
    func_020ac1e8((char *) param + 12);
    result = func_020ab270((char *) param + 132);
    if (result == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    ptr = (char *) param + 12;
    func_020ac11c(ptr, flag, 0);
}
