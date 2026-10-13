/* func_01ffcc10 @ 0x01ffcc10, 0x20 bytes, Thumb, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_01ffcc10 {
    unsigned char tag;
};
struct UnkStruct_01ffcc10_2 {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
};
struct UnkStruct_01ffcc10_3 {
    struct UnkStruct_01ffcc10 *unk_00;
    struct UnkStruct_01ffcc10_2 *p1;
};

int func_01ffcc10(void *unused, struct UnkStruct_01ffcc10_3 *p)
{
    if ((p->unk_00->tag & 0x1f) != 6) {
        return 1;
    }
    if (p->p1->unk_34 != 0) {
        return 0;
    }
    return 1;
}
