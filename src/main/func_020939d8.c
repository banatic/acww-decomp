/* func_020939d8 @ 0x020939d8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094bc0(void *param1);

void func_020939d8(void *param1)
{
    void *r4;
    unsigned int r0;
    unsigned int r1;

    r4 = param1;
    func_02094bc0(r4);
    r1 = 0x00000c00;
    r0 = *(unsigned int *) ((char *) r4 + 0xc);
    *(unsigned int *) ((char *) r0 + 0x50) = r1;
}
