/* func_ov004_0223a740 @ 0x0223a740, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223a770(void *self);

int func_ov004_0223a740(void *self)
{
    return *(unsigned short *) ((char *) func_ov004_0223a770(self) + 0x4);
}
