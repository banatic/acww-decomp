/* func_02069168 @ 0x02069168, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a873c(void *, void *);

typedef struct Vtbl {
    char pad_00[0x64];
    void (*func)(void *, unsigned char);
} Vtbl;

typedef struct UnkStruct_02069168 {
    Vtbl *vtbl;
} UnkStruct_02069168;

void func_02069168(void *self)
{
    unsigned char local[8];
    unsigned char ch;
    void *ptr1;
    UnkStruct_02069168 *obj;
    Vtbl *vtbl;

    func_020a873c((char *) self + 0x2c, local);
    ptr1 = *(void **) ((char *) self + 0x24);
    obj = *(UnkStruct_02069168 **) ((char *) ptr1 + 0x14a8);
    ch = local[0];
    vtbl = obj->vtbl;
    vtbl->func(obj, ch);
}
