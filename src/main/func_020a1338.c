/* func_020a1338 @ 0x020a1338, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a1338 {
    char pad_00[0xCC];
    void *unk_CC;
};

extern struct UnkStruct_020a1338 *data_021f3c3c;

void *func_020a1338(void)
{
    struct UnkStruct_020a1338 *p;

    p = data_021f3c3c;
    if (p == 0) {
        return 0;
    }
    return p->unk_CC;
}
