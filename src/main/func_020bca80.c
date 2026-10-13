/* func_020bca80 @ 0x020bca80, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

typedef struct {
    unsigned char pad_00[0x2f30];
    int unk_2F30;
    unsigned char pad_2F34[0x2f48 - 0x2f30 - 4];
    int unk_2F48;
} UnkStruct_020bca80;

void func_020bca80(UnkStruct_020bca80 *s, int a, int b, int c)
{
    s->unk_2F48 = a;
    s->unk_2F30 = b + (c > 0 ? func_020644cc(c) : 0);
}
