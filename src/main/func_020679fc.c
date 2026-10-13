/* func_020679fc @ 0x020679fc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *arg);
extern void func_020a8c1c(char *ptr);
extern int func_02099870(int arg);
extern void func_02095074(int a, char *ptr);

int func_020679fc(char *arg)
{
    int t = func_020984e8(arg);
    func_020a8c1c(arg + 0x1cac);
    func_02095074(func_02099870(t), arg + 0x1cac);
    return 1;
}
