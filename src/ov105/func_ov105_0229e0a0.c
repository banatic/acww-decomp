/* func_ov105_0229e0a0 @ 0x0229e0a0, 0x30 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d908(void *param1, unsigned char param2);
extern int func_ov002_02209f9c(void *param1);
extern unsigned char *func_ov002_02208098(void *param1, unsigned char value);

void func_ov105_0229e0a0(void *param1)
{
    if (func_ov002_02209f9c((char *) param1 + 0x24a4)) {
        func_ov105_0229d908(param1, *(unsigned char *) ((char *) param1 + 0x2ba));
        func_ov002_02208098(param1, 0x11);
    }
}
