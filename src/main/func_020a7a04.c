/* func_020a7a04 @ 0x020a7a04, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a7a04 {
    char *data;
    int unk_04;
    int unk_08;
};

extern char data_020e3d14[];

void func_020a7a04(struct UnkStruct_020a7a04 *obj)
{
    obj->data = data_020e3d14;
    obj->unk_04 = 0;
    obj->unk_08 = 0;
}
