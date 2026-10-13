/* func_020780b8 @ 0x020780b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_020780b8;

extern char data_020e1888;
extern void func_020a8c38(void *);

UnkStruct_020780b8 *func_020780b8(UnkStruct_020780b8 *obj)
{
    obj->unk_00 = &data_020e1888;
    func_020a8c38(obj);
    return obj;
}
