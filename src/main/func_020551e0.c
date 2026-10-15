/* func_020551e0 @ 0x020551e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020551e0 {
    void *unk_00;
} UnkStruct_020551e0;

typedef struct UnkStruct_020551e0_2 {
    void *unk_00;
    char pad_04[0x9c - 4];
    UnkStruct_020551e0 sub;
} UnkStruct_020551e0_2;

extern void func_02057054(UnkStruct_020551e0 *sub);
extern void *func_0205572c(UnkStruct_020551e0_2 *self);

extern unsigned char data_020dd05c[];
extern unsigned char data_020dd06c[];

UnkStruct_020551e0_2 *func_020551e0(UnkStruct_020551e0_2 *self)
{
    self->unk_00 = (void *) data_020dd05c;
    self->sub.unk_00 = (void *) data_020dd06c;
    func_02057054(&self->sub);
    func_0205572c(self);
    return self;
}
