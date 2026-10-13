/* func_0203c57c @ 0x0203c57c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203c57c {
    char pad_00[0x9a];
    short unk_9A;
    char pad_9C[0xae];
    short unk_14A;
};

short func_0203c57c(struct UnkStruct_0203c57c *arg)
{
    return arg->unk_14A + arg->unk_9A;
}
