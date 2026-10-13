/* func_ov052_022608b4 @ 0x022608b4, 0xa8 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201b420(unsigned char *, unsigned char *);
extern void func_0209a000(unsigned char *, int);
extern void func_020ad890(unsigned int, unsigned int, int);
extern void func_020984e8(void);
extern int func_02099870(void);
extern void func_020871dc(void *, int);
extern void func_020871d4(void *, unsigned char *);
extern void func_02015fb0(void *, unsigned char *, int, int, int, int);

extern int data_021f3aec;

typedef struct {
    char pad_00[0xB4];
    unsigned char *ptr;
    unsigned char *other;
} UnkStruct_022608b4;

void func_ov052_022608b4(UnkStruct_022608b4 *self)
{
    func_0201b420(self->ptr, self->other);
    func_0209a000(self->ptr + 0x71e, 0);
    func_020ad890(*(unsigned int *) (self->ptr + 0x728), *(unsigned int *) (self->ptr + 0x72c), 0xf);

    {
        void *p = (void *) &data_021f3aec;
        int ret;
        func_020984e8();
        ret = func_02099870();
        func_020871dc(p, ret);
        func_020871d4(p, self->ptr + 0x71e);
    }

    func_02015fb0(self, self->other, 2, 10, 0, 0);
    *(unsigned short *) (self->ptr + 0x71e) = 0xfff1;
    *(unsigned char *) (self->ptr + 0x732) = 1;
}
