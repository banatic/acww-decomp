/* func_ov047_0226107c @ 0x0226107c, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *self, int a);
extern void func_ov047_02261f84(void *self, int b);
extern unsigned short func_ov047_02261c00(void *argument0, int argument1);

void func_ov047_0226107c(void *param)
{
    func_020157d4(param, (unsigned int) func_ov047_02261c00, 13, 1);
    func_02015828(param, 0);
    func_ov047_02261f84(param, 1);
}
