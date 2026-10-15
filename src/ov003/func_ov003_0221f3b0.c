/* func_ov003_0221f3b0 @ 0x0221f3b0, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205577c(void *ptr);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*f1)(void *), void (*f2)(void *));
extern void *func_020565b0(void *argument0);
extern void func_020565c8(void *argument0);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned char pad_08[0x98];
    unsigned int unk_A0;
    unsigned int unk_A4;
    unsigned int unk_A8;
} UnkStruct_0221f3b0;

#define VisitElement_020565c8 (void (*)(void *)) func_020565c8
#define VisitElement_020565b0 (void (*)(void *)) func_020565b0

UnkStruct_0221f3b0 *func_ov003_0221f3b0(UnkStruct_0221f3b0 *obj)
{
    func_0205577c(&obj->unk_04);
    __cxa_vec_ctor(&obj->unk_A8, 2, 0x20, VisitElement_020565c8, VisitElement_020565b0);
    obj->unk_00 = 0;
    obj->unk_A0 = 0;
    obj->unk_A4 = 0;
    return obj;
}

#undef VisitElement_020565c8
#undef VisitElement_020565b0
