/* func_020a8be4 @ 0x020a8be4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f450c;
extern void func_020a8d20(void *, int, int, int, int);
extern void func_020a922c(void *, int);
extern int func_020a8d08(void *);
extern void func_020a8d10(void *);

int func_020a8be4(int arg1, int arg2)
{
    int ret;
    func_020a8d20(&data_021f450c, arg1, arg2, 0, 0);
    func_020a922c(&data_021f450c, 0);
    ret = func_020a8d08(&data_021f450c);
    func_020a8d10(&data_021f450c);
    return ret;
}
