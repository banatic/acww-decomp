/* func_0203b144 @ 0x0203b144, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1f8];
    int unk_1F8;
} UnkStruct_0203b144;
extern UnkStruct_0203b144 *data_021c67a4;
extern int func_0203c0ac(UnkStruct_0203b144 *p, int flag);

int func_0203b144(void)
{
    UnkStruct_0203b144 *p;
    int field;
    p = data_021c67a4;
    field = p->unk_1F8;
    if (field == 9) {
        return 0;
    } else if (field == 0) {
        return 1;
    } else {
        return func_0203c0ac(p, 0);
    }
}
