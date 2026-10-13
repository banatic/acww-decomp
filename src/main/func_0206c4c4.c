/* func_0206c4c4 @ 0x0206c4c4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206d420(void *, int, int);

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_0206c4c4;

int func_0206c4c4(UnkStruct_0206c4c4 *s)
{
    return func_0206d420(s, s->unk_2C + 0x18ac, s->unk_2C);
}
