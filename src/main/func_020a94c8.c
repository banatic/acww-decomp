/* func_020a94c8 @ 0x020a94c8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a9354(void *param);

struct Unk020a94c8 {
    void *unk_00;
    int unk_04;
    int unk_08;
};

int func_020a94c8(struct Unk020a94c8 *obj, int value)
{
    obj->unk_04 = value;
    obj->unk_08 = value;
    return func_020a9354(obj->unk_00);
}
