/* func_ov142_0229b670 @ 0x0229b670, 0x28 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov142_02299830(int a);
extern void func_ov142_02299908(int a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov142_0229b670(int p)
{
    unsigned char f = data_021fbdd8;
    if (f) {
        func_ov142_02299830(p);
        return;
    }
    func_ov142_02299908(p);
    func_ov002_02208098((void *) (p), 0);
}
