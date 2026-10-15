/* func_ov050_02261494 @ 0x02261494, 0x34 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov050_022637c0(unsigned short *value, int event);
extern void func_020157d4(void *a, int (*callback)(unsigned short *, int), unsigned char c, unsigned char d);
extern int func_02015828(void *a, int b);
extern void func_ov050_02263b38(void *a, int b);

#define GroundPredicate ((int (*)(unsigned short *, int)) func_ov050_022637c0)

typedef struct {
    unsigned char pad_00[0xD0];
    unsigned int unk_D0;
} UnkStruct_02261494;

void func_ov050_02261494(UnkStruct_02261494 *self, int flag)
{
    if (flag == 0) {
        func_020157d4(self, GroundPredicate, 13, 0);
        func_02015828(self, 0);
        func_ov050_02263b38(self, 2);
    } else {
        self->unk_D0 = 15;
    }
}
