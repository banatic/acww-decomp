/* func_0208aecc @ 0x0208aecc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051ad8(void *obj);

struct UnkStruct_0208aecc {
    volatile void *unk_00;
};

extern unsigned char data_020da6dc[];
extern unsigned char data_020e2094[];

void *func_0208aecc(void *self)
{
    struct UnkStruct_0208aecc *obj = (struct UnkStruct_0208aecc *) self;
    obj->unk_00 = (void *) data_020da6dc;
    obj->unk_00 = (void *) data_020e2094;
    func_02051ad8(self);
    return self;
}
