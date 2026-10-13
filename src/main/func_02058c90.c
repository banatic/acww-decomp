/* func_02058c90 @ 0x02058c90, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205967c(void *s, char *p);
extern void VEC_Add(char *a, char *b, char *c);
extern void func_02059674(void *s, int x);

typedef struct {
    char pad_00[0x60];
    char unk_60;
    char pad_61[0x84 - 0x60 - 1];
    char unk_84;
    char pad_85[0xD6 - 0x84 - 1];
    unsigned short unk_D6;
} UnkStruct_02058c90;

void func_02058c90(UnkStruct_02058c90 *s)
{
    if ((int) s->unk_D6 >= 9) {
        return;
    }
    func_0205967c(s, &s->unk_60);
    VEC_Add(&s->unk_60, &s->unk_84, &s->unk_60);
    s->unk_D6++;
    if ((int) s->unk_D6 < 9) {
        return;
    }
    func_02059674(s, 0);
}
