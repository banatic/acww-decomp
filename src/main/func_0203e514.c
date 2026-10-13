/* func_0203e514 @ 0x0203e514, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern void func_0203e58c(int);
extern void func_0203e55c(int);
extern void func_0203e5f4(int);
extern void func_0203e5c0(int);
extern void func_0203f568(int);

extern unsigned char data_021c72c4[];

int func_0203e514(int param)
{
    if (func_0203ec98()) {
        func_0203e58c(param);
        func_0203e55c(param);
    }
    if (!func_0203ec98()) {
        func_0203e5f4(param);
    }
    if (func_0203ec98()) {
        func_0203e5c0(param);
    }
    func_0203f568((unsigned int) data_021c72c4);
    return 1;
}
