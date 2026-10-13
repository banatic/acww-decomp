/* func_0203f400 @ 0x0203f400, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);
extern int func_0203f454(unsigned char, int);

struct UnkStruct_0203f400 {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_0203f400 *data_020ccf94;

int func_0203f400(int p)
{
    struct UnkStruct_0203f400 *s = data_020ccf94;

    if (func_02073d90(s) == 0) {
        return 2;
    }
    if (s->unk_64 == 0) {
        if (!func_0203f454((unsigned char) s->unk_64, p)) {
            return 0;
        }
        return 2;
    }
    return 1;
}
