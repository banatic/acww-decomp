/* func_02066a04 @ 0x02066a04, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df008;
extern void func_020a81b8(void *);
extern void func_02066a9c(void *);

struct Func02066a04Sub {
    char data[0x20];
};

struct Func02066a04Obj {
    void *unk_00;
    char pad_04[0x1c];
    struct Func02066a04Sub sub;
    int unk_40;
    unsigned char unk_44;
};

struct Func02066a04Obj *func_02066a04(struct Func02066a04Obj *obj)
{
    func_020a81b8(obj);
    obj->unk_00 = &data_020df008;
    func_02066a9c(&obj->sub);
    obj->unk_40 = 0;
    obj->unk_44 = 0;
    return obj;
}
