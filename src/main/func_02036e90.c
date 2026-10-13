/* func_02036e90 @ 0x02036e90, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_02036e90;

void func_02036b14(UnkStruct_02036e90 *);
void func_02036af4(UnkStruct_02036e90 *);
void func_02036ad4(UnkStruct_02036e90 *);
void func_02036ab4(UnkStruct_02036e90 *);
void func_02036a94(UnkStruct_02036e90 *);
void func_02036a5c(UnkStruct_02036e90 *);

int func_02036e90(UnkStruct_02036e90 *obj)
{
    if (obj->unk_14 == 0) {
        func_02036b14(obj);
        func_02036af4(obj);
        func_02036ad4(obj);
        func_02036ab4(obj);
        func_02036a94(obj);
        func_02036a5c(obj);
    }
    obj->unk_15 = 0;
    return 0;
}
