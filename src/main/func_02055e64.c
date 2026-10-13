/* func_02055e64 @ 0x02055e64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ff8ad4(void *);

void func_02055e64(void *r0)
{
    void *r3 = (char *) r0 + 8;
    unsigned int r2 = *(unsigned int *) ((char *) r0 + 8);
    r2 |= 2;
    *(unsigned int *) ((char *) r0 + 8) = r2;
    func_01ff8ad4(r3);
}
