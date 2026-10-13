/* func_020aa79c @ 0x020aa79c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e406c;
extern void func_020aa82c(void *obj);
extern void func_020ac2ec(void *obj);
extern void func_020ab37c(void *dst, void *src);

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
    unsigned char sub_c[0x78];
    unsigned char sub_84[0x30];
    int unk_B4;
    int unk_B8;
    int unk_BC;
    unsigned char unk_C0;
} UnkStruct_020aa79c;

UnkStruct_020aa79c *func_020aa79c(UnkStruct_020aa79c *obj)
{
    func_020aa82c(obj);
    obj->unk_00 = &data_020e406c;
    obj->unk_08 = 0;
    func_020ac2ec(&obj->sub_c);
    func_020ab37c(&obj->sub_84, &obj->sub_c);
    obj->unk_B4 = 0;
    obj->unk_B8 = 0;
    obj->unk_BC = 0;
    obj->unk_C0 = 0;
    return obj;
}
