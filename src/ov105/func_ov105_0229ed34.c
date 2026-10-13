/* func_ov105_0229ed34 @ 0x0229ed34, 0x26 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *self, int flag);
extern unsigned int func_ov002_02207f60(void *self);
extern void func_ov105_0229ed04(void *self);

void func_ov105_0229ed34(void *self)
{
    if (func_ov002_02207f3c(self, -1) != 0) {
        func_ov105_0229ed04(self);
    }
    *(unsigned int *) ((char *) self + 0x9c) = func_ov002_02207f60(self);
}
