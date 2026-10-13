/* func_ov068_0226c7dc @ 0x0226c7dc, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea6e0(void *buf, int val);
extern int func_ov068_0226c820(void *a, void *b, void *c);

typedef struct UnkStruct_0226c7dc {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0x37];
    short unk_94;
    char pad_96[2];
    int unk_98;
} UnkStruct_0226c7dc;

int func_ov068_0226c7dc(void *a, UnkStruct_0226c7dc *b)
{
    int local[3];

    if (b->unk_98 != 0) {
        local[0] = 0;
        local[1] = 0;
        local[2] = 0x1000;
        func_020ea6e0(local, b->unk_94);
        return func_ov068_0226c820(a, &b->unk_5C, local);
    } else {
        return 0;
    }
}
