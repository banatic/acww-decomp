/* func_02016194 @ 0x02016194, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d8bd4;
extern void *func_02066994(void *);

struct UnkStruct_02016194 {
    void *unk_00;
};

void *func_02016194(void *self)
{
    struct UnkStruct_02016194 *obj = self;
    obj->unk_00 = &data_020d8bd4;
    func_02066994(obj);
    return obj;
}
