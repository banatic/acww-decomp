/* func_ov047_02260dbc @ 0x02260dbc, 0x34 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070edc(void *ptr);
extern void func_ov047_02261618(void *p);
extern void func_02015094(void *p);
extern int data_021f38f8;

typedef struct {
    char pad_00[0xD0];
    int unk_D0;
} UnkStruct_02260dbc;

void func_ov047_02260dbc(UnkStruct_02260dbc *p)
{
    func_ov047_02261618(p);
    if (func_02070edc(&data_021f38f8)) {
        p->unk_D0 = 49;
    } else {
        p->unk_D0 = 39;
    }
    func_02015094(p);
}
