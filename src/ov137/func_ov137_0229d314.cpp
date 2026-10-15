/* func_ov137_0229d314 @ 0x0229d314, 0x44 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

// The object, its base and its members are built by out-of-line
// constructors in ov002 and ov134; only the final vtable store is inline.
extern "C" {
void *func_ov002_02207f80(unsigned long size); // operator new
void *func_ov002_0220830c(void *self);         // base constructor
void *func_ov002_02209ccc(void *self);
void *func_ov002_0220b008(void *self);
void *func_ov134_0229bed4(void *self);
extern char data_ov137_0229d440[]; // vtable
}

struct UnkStruct_0229d314 {
    void *vtbl;
    char base_data[0x90];
    char m1[0x64];
    char m2[0x1cc];
    char m3[0x28b4];
};

extern "C" UnkStruct_0229d314 *func_ov137_0229d314()
{
    UnkStruct_0229d314 *obj = (UnkStruct_0229d314 *) func_ov002_02207f80(sizeof(UnkStruct_0229d314));
    if (obj != 0) {
        func_ov002_0220830c(obj);
        obj->vtbl = data_ov137_0229d440;
        func_ov002_02209ccc(obj->m1);
        func_ov002_0220b008(obj->m2);
        func_ov134_0229bed4(obj->m3);
    }
    return obj;
}
