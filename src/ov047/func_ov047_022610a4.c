/* func_ov047_022610a4 @ 0x022610a4, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *p, int arg2);
extern void func_ov047_02261f84(void *p, int arg2);
extern int func_ov047_02261ea4(void *argument0, int argument1);

void func_ov047_022610a4(void *p)
{
    func_020157d4(p, (unsigned int) func_ov047_02261ea4, 13, 1);
    func_02015828(p, 0);
    func_ov047_02261f84(p, 0);
}
