/* func_ov087_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_ov087_022790ac(void *, int);

typedef struct UnkStruct_02278a54 {
    void *vtable;
    int pad_04;
    void (*func)(void **);
} UnkStruct_02278a54;

typedef struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    UnkStruct_02278a54 *inner;
} UnkStruct_02278a54_2;

void func_ov087_02278a54(UnkStruct_02278a54_2 *self, int mode)
{
    switch (mode) {
        case 0:
            self->inner->func((void **) &self->inner);
            {
                int ret = func_0201c2a4(self, 4);
                func_02016108(&self->inner, ret);
            }
            func_ov087_022790ac(self, 1);
            break;
        case 8:
            func_ov087_022790ac(self, 0);
            break;
    }
}
