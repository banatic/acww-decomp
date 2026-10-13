/* func_020aaeb4 @ 0x020aaeb4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int param0;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14[5];
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char unk_31;
    int unk_34;
} UnkStruct_020aaeb4;

void func_020aaeb4(UnkStruct_020aaeb4 *arg0, int arg1)
{
    unsigned int i;
    arg0->param0 = arg1;
    arg0->unk_04 = 0;
    arg0->unk_08 = 0x800;
    arg0->unk_0C = 0x800;
    arg0->unk_10 = 0;
    arg0->unk_28 = 0;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
    arg0->unk_31 = 0;
    arg0->unk_34 = 0;
    for (i = 0; i < 5; i++) {
        arg0->unk_14[i] = 0;
    }
}
