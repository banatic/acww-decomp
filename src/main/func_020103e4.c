/* func_020103e4 @ 0x020103e4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205ddd4(void *ptr);
extern int func_0205de24(void *ptr);

struct UnkStruct_020103e4 {
    char pad_00[0x59c];
    char unk_59C[1];
    char pad_59D[0xc8c - 0x59c - 1];
    int unk_C8C;
};

void func_020103e4(struct UnkStruct_020103e4 *p)
{
    if (p->unk_C8C == 1) {
        int result = 1;
        if (func_0205ddd4(p->unk_59C) != 75) {
            result = func_0205de24(p->unk_59C);
        }
        if (result != 0) {
            p->unk_C8C = 2;
        }
    }
}
