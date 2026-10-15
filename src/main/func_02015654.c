/* func_02015654 @ 0x02015654, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02015654 {
    char pad_00[0x40];
    int *ptr;
    char pad_44[0x44];
    unsigned char unk_88;
    char pad_89[0x23];
    unsigned char unk_AC;
};

extern int func_0206fbc0(void);

int func_02015654(void *param)
{
    struct UnkStruct_02015654 *s = (struct UnkStruct_02015654 *) param;
    int ret = 0;
    if (func_0206fbc0() != 0) {
        if (s->unk_88 != 1) {
            *(int *) ((char *) s->ptr + 8) = 1;
        }
        s->unk_AC = 3;
        ret = 1;
    }
    return ret;
}
