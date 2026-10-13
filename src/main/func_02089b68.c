/* func_02089b68 @ 0x02089b68, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a088(void *obj);
extern char data_020e2030;

typedef struct {
    void *unk_00;
} UnkStruct_02089b68;

UnkStruct_02089b68 *func_02089b68(UnkStruct_02089b68 *obj)
{
    func_0208a088(obj);
    obj->unk_00 = &data_020e2030;
    return obj;
}
