/* func_02083bac @ 0x02083bac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(int a, int b, int c, void (*d)());
extern void func_02083cb4(int a);
extern void func_0205cce4(void);

int func_02083bac(int param)
{
    func_02138c48(param + 1, 3, 1, func_0205cce4);
    func_02083cb4(param);
    return param;
}
