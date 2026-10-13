/* func_020b9adc @ 0x020b9adc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ce4(void *param);
extern void func_020ba108(void *param);

void func_020b9adc(void *param)
{
    void *r4;
    r4 = param;
    func_020b9ce4(r4);
    r4 = (char *) r4 + 0x24;
    func_020ba108(r4);
}
