/* func_ov105_0229d154 @ 0x0229d154, 0x28 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov002_02209d84(void *p);
extern unsigned int func_ov002_02209d7c(void *p);

void func_ov105_0229d154(char *obj)
{
    *(unsigned int *) (obj + 0xac) = func_ov002_02209d84((void *) (obj + 0x248c));
    *(unsigned int *) (obj + 0xb0) = func_ov002_02209d7c((void *) (obj + 0x248c));
}
