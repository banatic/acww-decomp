/* func_020689b4 @ 0x020689b4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020689b4 UnkStruct_020689b4;
typedef int (*Func)(UnkStruct_020689b4 *);
typedef struct Vtbl {
    char pad_00[0x6c];
    Func fn;
} Vtbl;
struct UnkStruct_020689b4 {
    Vtbl *vtbl;
};
typedef struct UnkStruct_020689b4_2 {
    char pad_00[0x14a8];
    UnkStruct_020689b4 *obj;
} UnkStruct_020689b4_2;
typedef struct Main {
    char pad_00[4];
    UnkStruct_020689b4_2 *inner;
    char pad_08[0x18 - 0x08];
    int unk_18;
    char pad_1C[0x20 - 0x1c];
    int unk_20;
    int unk_24;
} Main;

extern int func_02068958(Main *p);
extern int func_02004618(int v);

void func_020689b4(Main *p)
{
    int r4 = 5;
    if (p->unk_20 != 5) {
        r4 = p->unk_20;
    } else {
        if (func_02068958(p) == 0) {
            if (p->unk_18 == 3) {
                r4 = 1;
            } else {
                r4 = p->inner->obj->vtbl->fn(p->inner->obj);
            }
        }
    }
    p->unk_24 = r4;
    if (r4 != 5) {
        func_02004618(r4);
    }
}
