/* func_ov083_02278da4 @ 0x02278da4, 0x2c bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern void func_0203e020(void *ptr);
extern void func_ov083_02278e98(void *ptr, int x);

struct ov083_02278da4_struct {
    char pad_00[0x618];
    char unk_618;
};

int func_ov083_02278da4(struct ov083_02278da4_struct *p)
{
    if (func_02014868(&p->unk_618) == 0) {
        func_0203e020(p);
        func_ov083_02278e98(p, 2);
    }
    return 1;
}
