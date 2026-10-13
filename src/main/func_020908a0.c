/* func_020908a0 @ 0x020908a0, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    int unk_00;
    char rest[20];
};
struct UnkStruct_020908a0 {
    unsigned char idx;
    unsigned char pad_01[3];
    struct Entry entries[1];
};
struct Four {
    unsigned char d[4];
};

extern int func_02090a44(struct Entry *entry, int arg1, int arg2, int arg3, int arg4, struct Four f);

int func_020908a0(struct UnkStruct_020908a0 *b, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int result = 0;
    int i;
    unsigned char buf[4];

    buf[1] = (unsigned char) arg5;
    buf[2] = (unsigned char) arg6;
    for (i = 0; i < 32; i++) {
        int idx = b->idx;
        if (b->entries[idx].unk_00 == -1) {
            buf[0] = (unsigned char) idx;
            if (func_02090a44(&b->entries[idx], arg1, arg2, arg3, arg4, *(struct Four *) buf) != 0) {
                result = (int) &b->entries[b->idx];
                b->idx = (unsigned char) ((b->idx + 1) % 32);
                break;
            }
            break;
        } else {
            b->idx = (unsigned char) ((idx + 1) % 32);
        }
    }
    return result;
}
