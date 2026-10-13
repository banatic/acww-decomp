/* func_ov125_0229f928 @ 0x0229f928, 0x20 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a0ec(void *p);

typedef struct UnkStruct_0229f928 UnkStruct_0229f928;
typedef struct My My;

struct UnkStruct_0229f928 {
    char pad_00[0xc];
    void (*func)(void *);
};

struct My {
    char pad_00[0x644];
    UnkStruct_0229f928 *sub;
};

void func_ov125_0229f928(My *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub->func(&self->sub);
}
