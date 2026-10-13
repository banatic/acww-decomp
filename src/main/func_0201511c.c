/* func_0201511c @ 0x0201511c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(char *p);
extern int func_02019de8(char *p);
extern void func_02068434(void *p);
extern void func_02016004(void *p);

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x8];
    char *unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_0201511c;

int func_0201511c(UnkStruct_0201511c *s)
{
    int r = 0;
    if (s->unk_4C != 0 && s->unk_40 != 0) {
        if (func_02019e00(s->unk_4C + 0x564) == 0xf) {
            if (func_02019de8(s->unk_4C + 0x564) != 0) {
                func_02068434(s->unk_40);
                func_02016004(s);
                s->unk_AC = 2;
                r = 1;
            }
        }
    }
    return r;
}
