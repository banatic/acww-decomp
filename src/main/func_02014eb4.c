/* func_02014eb4 @ 0x02014eb4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x8];
    char *unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014eb4;

int func_02019e00(char *arg);
int func_02019de8(char *arg);
void func_02068434(void *arg);
void func_02016004(UnkStruct_02014eb4 *arg);

int func_02014eb4(UnkStruct_02014eb4 *s)
{
    int result = 0;

    if (s->unk_4C != 0 && s->unk_40 != 0) {
        if (func_02019e00(s->unk_4C + 0x564) == 0x11 && func_02019de8(s->unk_4C + 0x564) != 0) {
            func_02068434(s->unk_40);
            func_02016004(s);
            s->unk_AC = 2;
            result = 1;
        }
    }
    return result;
}
