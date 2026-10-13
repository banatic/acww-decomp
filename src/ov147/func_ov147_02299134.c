/* func_ov147_02299134 @ 0x02299134, 0x1e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_02299008(void *ptr);
extern void func_ov147_02299118(void *ptr);

void func_ov147_02299134(void *ptr)
{
    if (((unsigned char *) ptr)[0xaa] == 2) {
        func_ov147_02299008(ptr);
    } else {
        func_ov147_02299118(ptr);
    }
}
