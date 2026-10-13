/* func_020b866c @ 0x020b866c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b866c {
    char pad_00;
};

struct UnkStruct_020b866c_2 {
    char pad_00[8];
    struct UnkStruct_020b866c sub;
    char pad_09[0x108 - 0x08 - 1];
    int counter;
};

extern int func_0208a844(struct UnkStruct_020b866c *sub);
extern void func_020b884c(struct UnkStruct_020b866c_2 *self);
extern int func_020b8854(struct UnkStruct_020b866c_2 *self);
extern int func_020b9030(struct UnkStruct_020b866c *sub);
extern void func_0208a9ac(struct UnkStruct_020b866c *sub);
extern int func_020b904c(struct UnkStruct_020b866c *sub);
extern void func_020b88f0(struct UnkStruct_020b866c_2 *self, int value);

void func_020b866c(struct UnkStruct_020b866c_2 *self)
{
    if (self->counter > 0) {
        self->counter--;
    }
    if (func_0208a844(&self->sub) == 0) {
        func_020b884c(self);
    } else {
        if (func_020b8854(self) == 0) {
            if (func_020b9030(&self->sub) == 0) {
                func_0208a9ac(&self->sub);
            }
        } else {
            if (func_020b904c(&self->sub) != 0) {
                func_020b88f0(self, 0);
            }
        }
    }
}
