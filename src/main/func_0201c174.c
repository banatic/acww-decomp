/* func_0201c174 @ 0x0201c174, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201c174 UnkStruct_0201c174;
typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    char pad_00[0x78];
    int (*func)(UnkStruct_0201c174 *);
};

struct UnkStruct_0201c174 {
    ObjVtbl *vtbl;
};

extern int data_020c8178[];

int func_0201c174(UnkStruct_0201c174 *obj)
{
    int index = obj->vtbl->func(obj);
    if (index >= 2) {
        index = 0;
    }
    return data_020c8178[index];
}
