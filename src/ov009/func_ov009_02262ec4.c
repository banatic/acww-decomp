/* func_ov009_02262ec4 @ 0x02262ec4, 0xe bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_02262ec4(void *r0, void *r1);

void func_ov009_02262ec4(void *r0, void *r1)
{
    *(unsigned int *) (r0) = *(unsigned int *) ((char *) r1 + 0x5c);
    *(unsigned int *) ((char *) r0 + 4) = *(unsigned int *) ((char *) r1 + 0x60);
    *(unsigned int *) ((char *) r0 + 8) = *(unsigned int *) ((char *) r1 + 0x64);
}
