/* func_0203837c @ 0x0203837c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b54(void *p);
extern void func_02001b1c(void *p);
extern void func_02001bc4(void *p);
extern void func_02001b8c(void *p);

typedef struct {
    unsigned char pad_00[0xca];
    unsigned char flag;
    unsigned char other;
    unsigned char pad_CC[4];
    void *p0;
    void *p1;
    void *p2;
    void *p3;
} UnkStruct_0203837c;

void func_0203837c(UnkStruct_0203837c *self)
{
    if (self->flag) {
        self->flag = 0;
        func_02001b54(self->p0);
        func_02001b1c(self->p1);
        func_02001bc4(self->p2);
        func_02001b8c(self->p3);
        self->other = 1;
    }
}
