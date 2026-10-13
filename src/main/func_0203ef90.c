/* func_0203ef90 @ 0x0203ef90, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203ef90 {
    int pad_00[3];
    int unk_0C;
};

extern struct UnkStruct_0203ef90 *func_02065c00(void *a, int b);
extern char data_021c72cc;

int func_0203ef90(int param)
{
    struct UnkStruct_0203ef90 *result = func_02065c00(&data_021c72cc, param);
    return result ? result->unk_0C : 0;
}
