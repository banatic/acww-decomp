/* func_ov077_022793f8 @ 0x022793f8, 0x1c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201b790(void *);

typedef struct {
    unsigned char pad_00[0x654];
    int unk_654;
} UnkStruct_022793f8;

int func_ov077_022793f8(UnkStruct_022793f8 *self)
{
    if (self->unk_654 != 3) {
        func_0201b790(self);
    }
    return 1;
}
