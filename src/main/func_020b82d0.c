/* func_020b82d0 @ 0x020b82d0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *param, int a, int b, void (*cb)(void));
extern void func_020b8020(void);

void *func_020b82d0(void *param)
{
    func_02138c48(param, 0xa, 0x44, func_020b8020);
    return param;
}
