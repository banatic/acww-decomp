/* func_ov119_0229bba8 @ 0x0229bba8, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(int, void *, int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void func_ov119_0229b9a4(int);

void func_ov119_0229bba8(int arg0, unsigned char arg1)
{
    unsigned char local_0;
    unsigned char *local_ptr;

    local_ptr = &local_0;
    local_0 = data_021f43ec;
    *local_ptr = arg1;
    func_ov002_0220b9b8(arg0 + 0x1efc, local_ptr, 1, 0);
    func_ov002_02208098(arg0, 0xd);
    func_ov119_0229b9a4(arg0);
}
