/* func_020030bc @ 0x020030bc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d7204;
extern int func_02064b18(void *ptr);

struct UnkStruct_020030bc {
    char pad_00[0x4c];
    int unk_4C;
};

int func_020030bc(struct UnkStruct_020030bc *param)
{
    int result;
    result = func_02064b18(&data_020d7204);
    param->unk_4C = result;
    if (result) {
        return 1;
    } else {
        return 0;
    }
}
