/* func_ov073_02278e58 @ 0x02278e58, 0x24 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201612c(void *);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

extern Pair __ptmf_null;

struct ObjStruct {
    char pad_00[0xb8];
    Pair sub;
};

void func_ov073_02278e58(struct ObjStruct *obj)
{
    func_0201612c(obj);
    obj->sub = __ptmf_null;
}
