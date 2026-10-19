/* func_ov107_0229cb14 @ 0x0229cb14, 0x28 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220a720(void *addr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0200467c(unsigned int cmd);

void func_ov107_0229cb14(void *param)
{
    func_ov002_0220a720((char *) param + 0x2828, 9);
    func_ov002_02208098((void *) (param), 15);
    func_0200467c(0x28);
}
