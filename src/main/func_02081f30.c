/* func_02081f30 @ 0x02081f30, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x54];
    int unk_54;
    int unk_58;
    char unk_5C[0x0e];
    unsigned short unk_6A;
} UnkStruct_02081f30;

extern void *func_0209529c(void *);
extern void func_020642fc(void *);
extern void func_02081ef0(void *);

UnkStruct_02081f30 *func_02081f30(UnkStruct_02081f30 *obj)
{
    func_0209529c(obj);
    obj->unk_54 = 0;
    obj->unk_58 = 0;
    func_020642fc(obj->unk_5C);
    obj->unk_6A = 0xfff1;
    func_02081ef0(obj);
    return obj;
}
