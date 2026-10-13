/* func_0208194c @ 0x0208194c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208194c {
    unsigned char pad_00[0x7c];
    unsigned short unk_7C;
};

int func_0208194c(struct UnkStruct_0208194c *arg)
{
    if ((((unsigned int) arg->unk_7C << 20) >> 31) == 0) {
        return 0;
    }
    return 1;
}
