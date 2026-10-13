/* func_ov105_0229cd30 @ 0x0229cd30, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a374(void *ptr, int size);
extern void func_ov002_02208098(void *ptr, int size);
extern void func_ov105_0229c330(void *ptr, int size);

void func_ov105_0229cd30(void *arg0)
{
    func_ov002_0220a374((char *) arg0 + 0x24a4, 4);
    func_ov002_02208098(arg0, 0x10);
    func_ov105_0229c330(arg0, 0x1000);
}
