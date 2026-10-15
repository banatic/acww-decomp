/* func_0208b800 @ 0x0208b800, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned int unk_7C;
    unsigned char unk_80;
    unsigned char unk_81;
    unsigned char unk_82;
} ExampleStruct;

extern int func_0208b720(void *receiver);
extern void func_0208b77c(ExampleStruct *self);

void func_0208b800(ExampleStruct *self)
{
    self->unk_7C = func_0208b720(self);
    func_0208b77c(self);
    self->unk_81 = 0;
    self->unk_82 = 0;
}
