/* func_0201a9f4 @ 0x0201a9f4, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201aa10(void *obj, int a1, unsigned int a2, unsigned int a3, unsigned char a4);

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char unk_60;
    unsigned int unk_64;
} UnkStruct_0201a9f4;

void func_0201a9f4(void *obj, int a1)
{
    UnkStruct_0201a9f4 *s = (UnkStruct_0201a9f4 *) obj;
    func_0201aa10(s, a1, s->unk_64, s->unk_5C, s->unk_60);
}
