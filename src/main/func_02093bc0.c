/* func_02093bc0 @ 0x02093bc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094bc0(void);

void func_02093bc0(void *arg0)
{
    unsigned int *ptr;
    void *r4 = arg0;

    func_02094bc0();
    ptr = *(unsigned int **) ((char *) r4 + 0xc);
    *(unsigned int *) ((char *) ptr + 0x54) = 0x1333;
}
