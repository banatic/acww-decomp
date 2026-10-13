/* func_0209ae70 @ 0x0209ae70, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

func_0209ae70(unsigned int param1, unsigned int param2, unsigned int param3)
{
    unsigned short local_0;
    func_0209af04();
    local_0 = 0xfff1;
    func_0209bd30(param1 + 0x10, 0x15, &local_0, 0);
    func_0209bc24(param1 + 0x10, 0);
    func_02003728(param1, param2);
    MI_CpuCopy8(param3, param1 + 0x1c, 8);
}
