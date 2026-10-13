/* func_0205bfd0 @ 0x0205bfd0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205bfd0(void *r0, int r1, int r2);

void *func_0205bfd0(void *r0, int r1, int r2)
{
    *(int *) ((char *) r0 + 0x14) = r2;
    *(int *) ((char *) r0 + 0x10) = r1;
    *(unsigned char *) r0 = 2;
    return (void *) 1;
}
