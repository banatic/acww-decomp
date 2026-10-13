/* func_020a9ddc @ 0x020a9ddc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned char unk_0C;
    unsigned char pad_0D[0x147];
    unsigned char unk_154;
} SELF;

extern int func_020aae84(unsigned char *);
extern void func_020ac46c(unsigned char *, int);
extern void func_020ac4ec(unsigned char *);

void func_020a9ddc(SELF *self)
{
    func_020ac46c(&self->unk_0C, func_020aae84(&self->unk_154));
    func_020ac4ec(&self->unk_0C);
}
