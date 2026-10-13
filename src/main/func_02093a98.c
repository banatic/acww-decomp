/* func_02093a98 @ 0x02093a98, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094bc0(void *);

void func_02093a98(void *r0)
{
    void *r4;
    unsigned int r1;
    unsigned int *r0_2;

    r4 = r0;
    func_02094bc0(r4);
    r1 = 0x800;
    r0_2 = *(unsigned int **) ((char *) r4 + 0xc);
    r0_2[0x14] = r1;
}
