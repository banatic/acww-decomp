/* func_0208dd18 @ 0x0208dd18, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x4E];
    unsigned char unk_4E;
    unsigned char unk_4F;
} UnkStruct_0208dd18;

extern unsigned char data_020e54a8;

void func_0208dd18(UnkStruct_0208dd18 *p)
{
    int flag;
    int val;
    flag = 1;
    p->unk_4E = 1;
    if (data_020e54a8 != 1) {
        flag = 0;
    }
    if (flag) {
        val = 1;
    } else {
        val = 0;
    }
    p->unk_4F = val;
}
