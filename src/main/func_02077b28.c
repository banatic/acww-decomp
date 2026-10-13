/* func_02077b28 @ 0x02077b28, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02077b28(const unsigned char *byte)
{
    if (*byte & 0x80) {
        return 1;
    }
    return 0;
}
