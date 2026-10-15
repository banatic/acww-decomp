/* func_ov136_0229cab4 @ 0x0229cab4, 0x7c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    unsigned char unk_94;
    char pad_95[0x2c4 - 0x94 - 1];
    unsigned char unk_2C4;
    char pad_2C5[0x2b77 - 0x2c4 - 1];
    unsigned char unk_2B77;
} UnkStruct_ov136;

extern int func_0208e484(void *ptr);
extern int func_ov136_0229c574(void *self, int n);
extern int func_ov134_02299b70(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov134_022997b0(void *ptr);
extern void func_ov136_0229c8d4(void *self);
extern void func_ov136_0229c628(void *self);
extern void func_ov136_0229c92c(void *self);
extern void func_ov136_0229c900(void *self, int n);

void func_ov136_0229cab4(UnkStruct_ov136 *self)
{
    if (func_0208e484(&self->unk_94) != 0) {
        if (func_ov136_0229c574(self, 2) != 0) {
            if (func_ov134_02299b70(&self->unk_2C4) != 0) {
                func_ov002_02208098((void *) (self), 8);
                return;
            } else {
                if (func_ov134_022997b0(&self->unk_2C4) != 0) {
                    func_ov136_0229c8d4(self);
                    return;
                } else {
                    func_ov002_02208098((void *) (self), 7);
                    func_ov136_0229c628(self);
                }
            }
        } else {
            if (self->unk_2B77 == 2) {
                func_ov136_0229c92c(self);
                return;
            } else {
                func_ov136_0229c900(self, self->unk_2B77 + 3);
            }
        }
    }
}
