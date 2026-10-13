/* func_020afb48 @ 0x020afb48, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7a8;
extern int func_0209f150(void *ptr, int n);

typedef struct {
    char pad_00[0x52];
    unsigned char unk_52;
    unsigned char unk_53;
    unsigned char unk_54;
} UnkStruct_020afb48;

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_020afb48_2;

int func_020afb48(UnkStruct_020afb48 *p1, UnkStruct_020afb48_2 *p2)
{
    if (func_0209f150(&data_021dc7a8, 5) != 0) {
        if (p1->unk_54 == p2->unk_05) {
            if (p1->unk_53 == p2->unk_04) {
                if (p1->unk_52 == p2->unk_03) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
