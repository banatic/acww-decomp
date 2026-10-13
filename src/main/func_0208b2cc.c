/* func_0208b2cc @ 0x0208b2cc, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208d01c(void *);
extern void func_0208dd10(void *);
extern int func_0208dd00(void *);
extern void func_0208b1a0(void *);
extern void func_0208b2b0(void *);
extern void func_0208dd18(void *);

typedef struct {
    char pad_00[8];
    char unk_08[0xe0 - 8];
    char unk_E0[1];
    char pad_E1[0x348 - 0xe0 - 1];
    unsigned char flag348;
    unsigned char flag349;
} UnkStruct_0208b2cc;

void func_0208b2cc(UnkStruct_0208b2cc *self)
{
    int flag = (self->flag348 != 0) || (self->flag349 != 0);
    int res = !func_0208d01c(&self->unk_E0);
    if (flag || res) {
        func_0208dd10(&self->unk_08);
        if (func_0208dd00(&self->unk_08) != 0) {
            if (flag) {
                func_0208b1a0(self);
            } else {
                func_0208b2b0(self);
            }
        }
    } else {
        func_0208dd18(&self->unk_08);
    }
}
