/* func_02069100 @ 0x02069100, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fc00(void *);
extern void func_02068e44(void *);
extern void *func_0208fd68(void *);
extern void *func_0208a41c(void *);

typedef struct {
    char pad_00[0xc];
    char unk_0C;
    char pad_0D[0x43];
    char unk_50;
} UnkStruct_02069100;

void *func_02069100(UnkStruct_02069100 *self)
{
    func_0208fc00(&self->unk_50);
    func_02068e44(self);
    func_0208fd68(&self->unk_50);
    func_0208a41c(&self->unk_0C);
    return self;
}
