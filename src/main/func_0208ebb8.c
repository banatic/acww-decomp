/* func_0208ebb8 @ 0x0208ebb8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2330;
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

typedef struct {
    void *unk_00;
    char pad_04[0x10];
    char unk_14;
    char pad_15[0x13];
    char unk_28;
} UnkStruct_0208ebb8;

UnkStruct_0208ebb8 *func_0208ebb8(UnkStruct_0208ebb8 *obj)
{
    obj->unk_00 = &data_020e2330;
    func_0208a1f4(&obj->unk_28);
    func_0208a1f4(&obj->unk_14);
    func_0208af00(obj);
    return obj;
}
