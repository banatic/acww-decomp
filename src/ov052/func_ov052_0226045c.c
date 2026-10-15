/* func_ov052_0226045c @ 0x0226045c, 0x44 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *obj, int a, int b, void (*callback3)(void *));
extern void *func_ov052_02261128(void *obj);
extern void *func_0202ee5c(void *obj);
extern void func_020edf54(void *obj);
extern void func_020051b0(void *element);
extern int data_ov052_02261f40;

typedef struct UnkStruct_0226045c {
    int *unk_00;                     // offset 0
    char pad_04[0x654];              // 0x004 .. 0x657
    char unk_658;                    // 0x658
    char pad_659[0x720 - 0x658 - 1]; // 0x659 .. 0x71F
    char unk_720;                    // 0x720
} UnkStruct_0226045c;

#define DisposeElement_func_020051b0 ((void (*)(void *)) func_020051b0)

UnkStruct_0226045c *func_ov052_0226045c(UnkStruct_0226045c *self)
{
    self->unk_00 = &data_ov052_02261f40;
    __cxa_vec_cleanup(&self->unk_720, 3, 2, DisposeElement_func_020051b0);
    func_ov052_02261128(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

#undef DisposeElement_func_020051b0
