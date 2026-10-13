/* func_ov003_0220fe04 @ 0x0220fe04, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self, int arg);
extern int func_0200f434(void *self, int *arr);
extern void func_ov003_0220ff14(void *self);
extern void func_02010d64(void *self);
extern void func_ov003_0220fe4c(void *self);

typedef struct {
    char pad_00[0x7d4];
    int arr[3];
} UnkStruct_0220fe04;

void func_ov003_0220fe04(UnkStruct_0220fe04 *self)
{
    int local[3];
    int *p = self->arr;
    func_02010f5c(self, 0x7d4);
    local[0] = self->arr[0];
    local[1] = p[1];
    local[2] = p[2];
    if (func_0200f434(self, local)) {
        func_ov003_0220ff14(self);
    }
    func_02010d64(self);
    func_ov003_0220fe4c(self);
}
