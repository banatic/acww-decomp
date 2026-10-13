/* func_020548cc @ 0x020548cc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad_60[0x94];
    int unk_F4;
} UnkStruct_020548cc;

extern int func_02055140(void *a, int b);
extern int func_02056548(int a, void *b, int c);
extern int data_020dd030;

int func_020548cc(UnkStruct_020548cc *a, int b)
{
    if (func_02055140(a, b) == 0) {
        return 0;
    }
    a->unk_F4 = func_02056548(a->unk_5C, &data_020dd030, b);
    if (a->unk_F4 != 0) {
        return 1;
    } else {
        return 0;
    }
}
