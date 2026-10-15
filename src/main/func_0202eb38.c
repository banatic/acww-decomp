/* func_0202eb38 @ 0x0202eb38, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0202eb38 {
    void *unk_00;
} UnkStruct_0202eb38;
extern void *func_0201615c(UnkStruct_0202eb38 *);
extern void func_020edb3c(UnkStruct_0202eb38 *);
extern unsigned char data_020d9ff8[];

UnkStruct_0202eb38 *func_0202eb38(UnkStruct_0202eb38 *self)
{
    self->unk_00 = (void *) data_020d9ff8;
    func_0201615c(self);
    func_020edb3c(self);
    return self;
}
