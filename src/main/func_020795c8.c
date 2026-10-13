/* func_020795c8 @ 0x020795c8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd80(void *);
extern void func_0209c53c(void *);
extern void func_02079448(void *);

typedef struct {
    char unk_00[0x04];
    void *unk_04;
    char unk_08[0x08];
    void *unk_10;
    char unk_14[0x12];
    unsigned short unk_26;
    void *unk_28;
} UnkStruct_020795c8;

UnkStruct_020795c8 *func_020795c8(UnkStruct_020795c8 *obj)
{
    func_0209bd80(&obj->unk_04);
    func_0209c53c(&obj->unk_10);
    obj->unk_26 = 0xfff1;
    func_02079448(&obj->unk_28);
    return obj;
}
