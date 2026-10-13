/* func_02051340 @ 0x02051340, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051458(void *);

void func_02051340(void *r0)
{
    unsigned char b;
    int i;

    func_02051458(r0);
    b = *(unsigned char *) ((char *) r0 + 0x74);
    *(unsigned char *) ((char *) r0 + 0x38) = b;
    i = 0;
    *(int *) ((char *) r0 + 0x64) = ~i;
    *(int *) ((char *) r0 + 0x68) = *(int *) ((char *) r0 + 0x30);
    *(int *) ((char *) r0 + 0x78) = i;
}
