/* func_ov070_0227968c @ 0x0227968c, 0x34 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov070_02279dbc;
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

struct UnkStruct_0227968c {
    void *unk_00;
    unsigned char pad_04[0xc0];
    unsigned char unk_C4;
};

extern void func_020051b0(void *arg0);

#define DisposeElement_func_020051b0 ((void (*)(void *)) func_020051b0)

struct UnkStruct_0227968c *func_ov070_0227968c(struct UnkStruct_0227968c *p)
{
    p->unk_00 = &data_ov070_02279dbc;
    __cxa_vec_cleanup(&p->unk_C4, 3, 2, DisposeElement_func_020051b0);
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}

#undef DisposeElement_func_020051b0
