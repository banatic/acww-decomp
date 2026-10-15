/* func_ov003_0220f8e0 @ 0x0220f8e0, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_ov003_0220f768(void *, int, int, unsigned char, int, int, int);
extern int func_02008258(void *, int);
extern int func_0200d4e8(void *, int, int, int);

void func_ov003_0220f8e0(void *self)
{
    typedef struct {
        int field0;
        int field4;
        unsigned char pad[3];
        unsigned char field_b;
        unsigned char field_c;
    } UnkStruct_0220f8e0;
    UnkStruct_0220f8e0 *sub = (UnkStruct_0220f8e0 *) ((char *) self + 0x7d4);
    if (sub->field_c) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_ov003_0220f768(self, sub->field0, sub->field4, sub->field_b, 1, 6, -1);
        }
    } else {
        if (*(int *) ((char *) self + 0x818) == 1) {
            sub->field_c = 1;
            *(unsigned char *) ((char *) self + 0x2e4) = 1;
        } else if (*(int *) ((char *) self + 0x818) == 2) {
            int tmp = func_02008258(self, *(int *) ((char *) self + 0x7f0));
            *(int *) ((char *) self + 0x7fc) = tmp;
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}
