/* func_ov132_0229aff8 @ 0x0229aff8, 0x70 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_020983f0(int *);
extern void func_ov132_0229af54(char *, int);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern void func_ov132_0229b068(char *);

void func_ov132_0229aff8(char *arg)
{
    if (func_020983f0((int *) func_020992fc((int) func_020984e8())) == 0x3b9ac9ff) {
        func_ov132_0229af54(arg, 14);
        return;
    }
    arg[0x1505] = 0x35;
    func_0206fdd4(arg + 0x500, 6, 7, 0x19, 10, 7);
    func_0206fdd4(arg + 0xd00, 6, 7, 0x19, 10, 7);
    func_ov132_0229b068(arg);
}
