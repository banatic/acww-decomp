/* func_ov003_0221db30 @ 0x0221db30, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226539c(void *self);
extern int data_ov003_022390e8;
extern int data_ov003_022391ac;

typedef struct {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
} UnkStruct_0221db30;

void *func_ov003_0221db30(void *self)
{
    UnkStruct_0221db30 *p = (UnkStruct_0221db30 *) self;
    p->unk_00 = &data_ov003_022390e8;
    p->unk_EC = &data_ov003_022391ac;
    func_ov009_0226539c(self);
    return self;
}
