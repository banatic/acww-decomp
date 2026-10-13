/* func_02089aa8 @ 0x02089aa8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02089aa8 {
    char pad_00[0x1c];
    struct UnkStruct_02089aa8 *next;
    unsigned char unk_20;
    char pad_21[3];
    int unk_24;
} UnkStruct_02089aa8;

extern UnkStruct_02089aa8 *data_021d3124;
extern void *func_020b6590(void);
extern void func_020b7d84(void *, UnkStruct_02089aa8 *, int, int, int, unsigned char);

void func_02089aa8(UnkStruct_02089aa8 *self, int a1, int a2, int a3, unsigned char a4)
{
    self->next = 0;
    if (data_021d3124 == 0) {
        data_021d3124 = self;
    } else {
        self->next = data_021d3124;
        data_021d3124 = self;
    }
    self->unk_20 = 0;
    self->unk_24 = a2;
    func_020b7d84(func_020b6590(), self, a1, a3, 4, a4);
}
