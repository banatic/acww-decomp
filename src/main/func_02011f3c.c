/* func_02011f3c @ 0x02011f3c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char _pad[0x15];
    unsigned char value;
} data_021c14c4;

unsigned char func_02011f3c(void)
{
    return data_021c14c4.value;
}
