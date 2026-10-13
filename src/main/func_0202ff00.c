/* func_0202ff00 @ 0x0202ff00, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da18c;

typedef struct {
    char *unk_00;
    char pad_04[0x24];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
} UnkStruct_0202ff00;

void func_0202ff00(UnkStruct_0202ff00 *arg0)
{
    arg0->unk_00 = &data_020da18c;
    arg0->unk_28 = 0;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
    arg0->unk_34 = 0;
}
