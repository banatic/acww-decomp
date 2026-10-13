/* func_02020bf0 @ 0x02020bf0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02022454(void);

void func_02020bf0(unsigned char *r5, unsigned char *r4)
{
    unsigned char *r0;

    func_02022454();
    r0 = r5 + 0x104;
    *(unsigned int *) r4 = (unsigned int) r0;
    r0 = r5 + 0x122;
    *(unsigned char *) (r4 + 4) = *r0;
}
