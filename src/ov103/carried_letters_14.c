/* carried_letters_14: 3 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229c910 @ 0x0229c910, 0x54 bytes, Thumb
 * func_ov103_0229c8e8 @ 0x0229c8e8, 0x28 bytes, Thumb
 * func_ov103_0229c8a4 @ 0x0229c8a4, 0x44 bytes, Thumb
 */

typedef struct {
    char pad_00[0x2ba0];
    char data[0x200];
    unsigned char flag;
} UnkStruct_0229c8e8;

extern int func_ov103_0229cdfc(char *a, char *b);
extern int func_ov103_0229cde8(char *a, char *b);
extern int func_ov094_0229b8d8(char *ptr, int v);
extern int func_02066830(char *ptr, int v);
extern void func_ov094_0229b890(char *ptr, int v);
extern void func_ov103_0229cd1c(void *self, int arg1, char *data);

void func_ov103_0229c910(char *a, char *b)
{
    if (func_ov103_0229cdfc(a, b) != 0) {
        int tmp = func_ov103_0229cde8(a, b);
        a[0x2da0] = 1;
        func_02066830(a + 0x2ba0, func_ov094_0229b8d8(a + 0x0b2c, tmp));
        func_ov094_0229b890(a + 0x0b2c, tmp);
    }
}

void func_ov103_0229c8e8(UnkStruct_0229c8e8 *self, int arg1)
{
    if (self->flag == 1) {
        func_ov103_0229cd1c(self, arg1, self->data);
    }
    self->flag = 0;
}

void func_ov103_0229c8a4(unsigned char *p, void *q)
{
    if (p[0x2da0] == 1) {
        func_02066830((char *) (p + 0x2ca0), (int) (p + 0x2ba0));
        func_ov103_0229c910((char *) p, (char *) q);
        func_ov103_0229cd1c(p, (int) q, (char *) (p + 0x2ca0));
    }
}
