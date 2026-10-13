/* func_02019304 @ 0x02019304, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201afec(void *);
extern int func_0201c3dc(int);
extern int func_0201afe4(void *);
extern void func_0201b1a4(void *, void *, int *, int, int);
extern unsigned short data_020c80f8;

struct UnkStruct_02019304 {
    char pad_00[0x98];
    char flag;
    int *ptr;
};

struct UnkStruct_02019304_2 {
    char pad_00[0x8e];
    short val;
    char pad_90[0x350 - 0x90];
    int unk_350;
};

void func_02019304(struct UnkStruct_02019304 *a, struct UnkStruct_02019304_2 *b)
{
    if (func_0201c3dc((short) (func_0201afec(&b->unk_350) - b->val)) == 0) {
        return;
    }
    func_0201b1a4(&b->unk_350, b, a->ptr, func_0201afe4(&b->unk_350), data_020c80f8);
    a->flag = 1;
}
