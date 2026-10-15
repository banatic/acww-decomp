/* func_0206be94 @ 0x0206be94, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
    char pad_30[4];
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206be94;

extern int func_0206c234(int, int);
extern void func_0206be6c(UnkStruct_0206be94 *);
extern void func_02068104(int, int);

void func_0206be94(UnkStruct_0206be94 *s, int arg)
{
    if (*(unsigned char *) ((char *) s + 0x39)) {
        func_0206c234(s->unk_28, arg);
    }
    s->unk_38 = 0;
    if (s->unk_2C == 1) {
        s->unk_34--;
        if (s->unk_34 <= 0) {
            func_0206be6c(s);
        }
    } else if (s->unk_2C == 2) {
        func_02068104(s->unk_24, arg);
    }
}
