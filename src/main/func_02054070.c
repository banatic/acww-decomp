/* func_02054070 @ 0x02054070, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02054070 UnkStruct_02054070;
typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    void (*unk_00)(UnkStruct_02054070 *);
    void (*unk_04)(UnkStruct_02054070 *);
};

struct UnkStruct_02054070 {
    ObjVtbl *vtbl;
};

extern UnkStruct_02054070 *data_021c8ca0;
extern void func_02041c28(void);

void func_02054070(void)
{
    UnkStruct_02054070 *obj;
    obj = data_021c8ca0;
    if (obj) {
        obj->vtbl->unk_04(obj);
    }
    func_02041c28();
}
