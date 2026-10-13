/* func_0208e200 @ 0x0208e200, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e200(void *r0);

void func_0208e200(void *r0)
{
    unsigned char *r1;
    unsigned int *r0_32;
    unsigned int *r1_32;

    r0_32 = (unsigned int *) r0;
    r0_32[0x1C] = 1; // offset 0x70
    r1 = (unsigned char *) r0 + 0x7C;
    *r1 = 1;
    r1_32 = (unsigned int *) r0;
    r1_32[0x1E] = 3; // offset 0x78
    r1_32[0x0C] = 5; // offset 0x30
}
