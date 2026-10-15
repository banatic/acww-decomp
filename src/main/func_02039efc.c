/* func_02039efc @ 0x02039efc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039b30(void *);

void func_02039efc(int r0, int r1, int r2, int r3)
{
    *(int *) (r0 + 0xc) = r1;
    *(int *) (r0 + 0x14) = r2;
    *(int *) (r0 + 0x18) = r3;
    func_02039b30((void *) r0);
}
