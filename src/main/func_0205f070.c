/* func_0205f070 @ 0x0205f070, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205f2f0(void);
extern int func_02055b50(int, int);
extern int func_0205f150(int, int);
extern int func_021077e8(void);

int func_0205f070(int param1, int param2)
{
    int result;
    int temp;

    func_0205f2f0();
    temp = func_021077e8();
    result = func_0205f150(param1, param2);
    return func_02055b50(result, temp);
}
