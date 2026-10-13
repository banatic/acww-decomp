/* func_0206e890 @ 0x0206e890, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206e890 {
    int pad_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int pad_10;
    int pad_14;
    void *unk_18;
};

extern void FS_ConvertPathToFileID(struct UnkStruct_0206e890 *obj, int b, int c, int d);
extern void *func_020e98b4(int value);

int func_0206e890(struct UnkStruct_0206e890 *obj, int b, int c, int d)
{
    obj->unk_08 = c;
    obj->unk_0C = d;
    FS_ConvertPathToFileID(obj, b, c, d);
    obj->unk_18 = func_020e98b4(c << 3);
    return 1;
}
