/* func_ov147_02299154 @ 0x02299154, 0x12 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

void func_ov147_02299154(unsigned char *r0)
{
    unsigned char r1;
    r1 = *(unsigned char *) (r0 + 0xaa);
    if (r1 == 1) {
        *(unsigned int *) (r0 + 0xa4) = 0x64;
    }
}
