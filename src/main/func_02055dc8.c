/* func_02055dc8 @ 0x02055dc8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02105294(void *);

void func_02055dc8(void *r0, int r1, int r2)
{
    void *r5 = r0;
    int r4 = r2;
    func_02105294((char *) r0 + 8);
    *(int *) ((char *) r5 + 0x34) = r4;
}
