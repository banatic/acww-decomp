/* func_020aba8c @ 0x020aba8c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aba8c {
    char pad_00[0x143];
    unsigned char flag;
};

extern void func_020aba5c(struct UnkStruct_020aba8c *obj);

void func_020aba8c(struct UnkStruct_020aba8c *obj)
{
    if (obj->flag) {
        func_020aba5c(obj);
    }
}
