/* wfc_host_list_input_2: 2 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229a490 @ 0x0229a490, 0x20 bytes, Thumb
 * func_ov146_0229a464 @ 0x0229a464, 0x2c bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *param_0x15cc);

void func_ov146_0229a490(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x15cc);
    func_ov002_02208098(arg0, 7);
}

void func_ov146_0229a464(unsigned char *param)
{
    func_ov002_0220a164(param + 0x15cc);
    param[0xb3] = param[0x8d];
    func_ov002_02208098(param, 8);
}
