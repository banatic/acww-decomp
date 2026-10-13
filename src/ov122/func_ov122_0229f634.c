/* func_ov122_0229f634 @ 0x0229f634, 0x4e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f634 {
    char pad_00[0xf8];
    unsigned char unk_F8;
};

struct UnkStruct_0229f634_2 {
    char pad_00[0xaa];
    unsigned char kind;
    char pad_AB[0xbc - 0xab];
    struct UnkStruct_0229f634 *sub;
};

void *func_ov122_0229f634(struct UnkStruct_0229f634_2 *obj)
{
    switch (obj->kind) {
        case 0:
            return (char *) obj->sub + 0x44;
        case 1:
            return (char *) obj->sub + 0x44 + 2 * obj->sub->unk_F8;
        case 2:
            return (char *) obj->sub + 0x58;
        case 3:
            return (char *) obj->sub + 0xd8;
        default:
            return 0;
    }
}
