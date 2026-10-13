/* func_02054988 @ 0x02054988, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02054988 {
    unsigned char arr[2];
};

struct UnkStruct_02054988_2 {
    struct UnkStruct_02054988 *inner;
};

struct BigStruct {
    unsigned char pad_00[0xb4];
    int unk_B4;
    unsigned char pad_B8[0x3c];
    int unk_F4;
};

extern int func_01ffcc10(struct BigStruct *a, struct UnkStruct_02054988_2 *b);
extern int func_020549fc(struct BigStruct *a, int b);
extern void func_02054a9c(struct BigStruct *a, int x);
extern void func_020549d8(struct BigStruct *a, struct UnkStruct_02054988_2 *b);
extern void func_02054d80(struct BigStruct *a, struct UnkStruct_02054988_2 *b);

void func_02054988(struct BigStruct *a, struct UnkStruct_02054988_2 *b)
{
    if (func_01ffcc10(a, b) != 0) {
        return;
    }
    if (func_020549fc(a, b->inner->arr[1]) != 0) {
        func_02054a9c(a, a->unk_F4);
        func_020549d8(a, b);
    } else {
        func_02054a9c(a, a->unk_B4);
        func_02054d80(a, b);
    }
}
