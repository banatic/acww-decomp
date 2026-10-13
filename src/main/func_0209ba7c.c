/* func_0209ba7c @ 0x0209ba7c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b91c(void *a);
extern void func_0209bb90(int a, int b);
extern void func_0209bb68(int a, unsigned short *b);
extern int func_0209b908(void *a);
extern void func_02095238(int a);
extern unsigned short *func_0209b8c4(void *a);

void func_0209ba7c(void *param)
{
    unsigned short local;
    func_0209bb90(func_0209b91c(param), 0);
    local = 0xfff1;
    func_0209bb68(func_0209b91c(param), &local);
    func_02095238(func_0209b908(param));
    *func_0209b8c4(param) = 0xfff1;
}
