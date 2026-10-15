/* func_ov075_02278b00 @ 0x02278b00, 0x24 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02015590(void *p, int a);
extern void func_ov075_02278d44(void *p, int a);

void func_ov075_02278b00(void *p)
{
    func_020984e8();
    if (*(unsigned char *) ((char *) p + 0x1e) == 0x1a) {
        func_02015590(p, 0);
        func_ov075_02278d44(p, 1);
    }
}
