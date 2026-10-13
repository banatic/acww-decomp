/* func_0201c154 @ 0x0201c154, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c8190[];

typedef struct UnkStruct_0201c154 UnkStruct_0201c154;
typedef struct Vtbl Vtbl;

struct Vtbl {
    unsigned char pad_00[0x78];
    int (*method)(UnkStruct_0201c154 *);
};

struct UnkStruct_0201c154 {
    Vtbl *vtbl;
};

int func_0201c154(UnkStruct_0201c154 *obj)
{
    int res;
    res = obj->vtbl->method(obj);
    if (res >= 2) {
        res = 0;
    }
    return data_020c8190[res];
}
