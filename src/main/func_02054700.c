/* func_02054700 @ 0x02054700, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used

void func_02054700(unsigned int *r0)
{
    unsigned int *r1;
    unsigned int r2;

    r2 = 0;
    r1 = r0 + 0x54; // 0x150 / 4
    *r1 = r2;
    r2 = *r1;
    *(r0 + 0x53) = r2; // 0x14c / 4
}
