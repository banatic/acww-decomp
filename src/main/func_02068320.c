/* func_02068320 @ 0x02068320, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206684c(void *);

struct UnkStruct_02068320 {
    char unk_00[0x14a8];
    void *unk_14A8;
};

void func_02068320(struct UnkStruct_02068320 *obj)
{
    if (obj->unk_14A8) {
        func_0206684c(obj->unk_14A8);
        obj->unk_14A8 = 0;
    }
}
