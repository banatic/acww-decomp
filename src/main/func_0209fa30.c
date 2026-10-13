/* func_0209fa30 @ 0x0209fa30, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_0209fa30;

int func_0209fa30(UnkStruct_0209fa30 *s)
{
    if (s->unk_03 == 0) {
        return 0;
    }
    return 1;
}
