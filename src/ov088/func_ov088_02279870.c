/* func_ov088_02279870 @ 0x02279870, 0x30 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov088_02278c94(void *, void *);

int func_ov088_02279870(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov088_02278c94((char *) p + 0x658, p);
    return 1;
}
