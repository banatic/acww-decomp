/* func_ov122_022a07a4 @ 0x022a07a4, 0x30 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *p, unsigned char b);
extern void func_ov122_022a14c0(void *p);

void func_ov122_022a07a4(void *p)
{
    if ((data_021fbe40 & 0x200) != 0) {
        return;
    }
    func_ov002_02208098(p, ((unsigned char *) p)[0xb4]);
    func_ov122_022a14c0(p);
}
