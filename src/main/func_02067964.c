/* func_02067964 @ 0x02067964, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02067964 UnkStruct_02067964;
typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    unsigned char pad_00[0x68];
    int (*method)(UnkStruct_02067964 *);
};

struct UnkStruct_02067964 {
    ObjVtbl *vtbl;
};

typedef struct UnkStruct_02067964_2 {
    unsigned char pad_00[0x14A8];
    UnkStruct_02067964 *obj;
    unsigned char pad_14AC[0x1CEC - 0x14AC];
    char unk_1CEC;
} UnkStruct_02067964_2;

extern void func_020a8c1c(void *);
extern void func_0207eec4(int, void *);

int func_02067964(UnkStruct_02067964_2 *self)
{
    UnkStruct_02067964 *obj = self->obj;
    int res = obj->vtbl->method(obj);
    int ret = 0;
    func_020a8c1c(&self->unk_1CEC);
    if (res != 0) {
        func_0207eec4(res, &self->unk_1CEC);
        ret = 1;
    }
    return ret;
}
