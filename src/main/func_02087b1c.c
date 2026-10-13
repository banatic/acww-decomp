/* func_02087b1c @ 0x02087b1c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct bitflags {
    unsigned char bit0 : 1;
};

int func_02087b1c(struct bitflags *ptr)
{
    if (ptr->bit0) {
        return 1;
    } else {
        return 0;
    }
}
