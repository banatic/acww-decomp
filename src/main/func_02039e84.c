/* func_02039e84 @ 0x02039e84, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02039e84 {
    char pad_00[0x50];
    int unk_50;
};

struct Main {
    char pad_00[0x9c];
    struct UnkStruct_02039e84 *unk_9C;
    struct UnkStruct_02039e84 *unk_A0;
};

extern void func_02051694(struct UnkStruct_02039e84 *item);

void func_02039e84(struct Main *obj)
{
    if (obj->unk_9C) {
        obj->unk_9C->unk_50 = 3;
        func_02051694(obj->unk_9C);
    }
    if (obj->unk_A0) {
        obj->unk_A0->unk_50 = 3;
        func_02051694(obj->unk_A0);
    }
}
