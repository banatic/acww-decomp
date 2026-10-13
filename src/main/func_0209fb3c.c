/* func_0209fb3c @ 0x0209fb3c, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209fb3c {
    unsigned char pad_00[2];
    unsigned char flag;
};

int func_0209fb3c(struct UnkStruct_0209fb3c *s)
{
    if (s->flag == 2) {
        return 1;
    } else {
        return 0;
    }
}
