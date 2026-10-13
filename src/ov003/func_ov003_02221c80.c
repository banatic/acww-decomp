/* func_ov003_02221c80 @ 0x02221c80, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02221c80(void *r0, void *r1);

void func_ov003_02221c80(void *r0, void *r1)
{
    *(unsigned int *) ((char *) r0 + 0x18) = *(unsigned int *) ((char *) r1 + 0);
    *(unsigned int *) ((char *) r0 + 0x1c) = *(unsigned int *) ((char *) r1 + 4);
    *(unsigned int *) ((char *) r0 + 0x20) = *(unsigned int *) ((char *) r1 + 8);
    *(unsigned int *) ((char *) r0 + 0x30) = 0;
    *(unsigned int *) ((char *) r0 + 0x34) = 0xfffff400;
    *(unsigned int *) ((char *) r0 + 0x38) = 0;
}
