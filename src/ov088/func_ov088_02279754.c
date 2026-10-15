/* func_ov088_02279754 @ 0x02279754, 0x2c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov088_02279784(void *, int);

int func_ov088_02279754(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov088_02279784(self, 1);
    }
    return 1;
}
