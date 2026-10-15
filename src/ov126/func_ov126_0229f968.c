/* func_ov126_0229f968 @ 0x0229f968, 0x38 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206fc8c(void);
extern int func_020b1078(void *, void *);
extern void func_0206fc4c(int);
extern void func_020b141c(void *, void *);

typedef struct {
    char pad_00[0x4248];
    int unk_4248;
} UnkStruct_0229f968;

void func_ov126_0229f968(UnkStruct_0229f968 *self)
{
    void *result = func_0206fc8c();
    if (func_020b1078(&self->unk_4248, result)) {
        func_0206fc4c(0);
    }
    func_020b141c(&self->unk_4248, result);
}
