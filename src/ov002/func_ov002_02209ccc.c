/* func_ov002_02209ccc @ 0x02209ccc, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a40c(void *, unsigned int);
extern char data_ov002_0220bc50[];

void *func_ov002_02209ccc(void *self)
{
    func_ov002_0220a40c(self, 0);
    *(char **) self = data_ov002_0220bc50;
    return self;
}
