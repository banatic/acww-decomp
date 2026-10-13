/* func_ov003_0220fb94 @ 0x0220fb94, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220fcb4(void *);
extern int func_0200f434(void *, int *);
extern void func_ov003_0220fc88(void *);
extern void func_02010d64(void *);
extern int func_02073908(int, int);
extern void func_ov003_0220fc34(void *);
extern void func_ov003_0220fbf8(void *);
extern int data_020ccf94;

typedef struct {
    int pad_00;
    int b;
    int c;
    int d;
} Sub_t;

typedef struct {
    char pad_00[0x7d4];
    Sub_t sub;
    char pad1[0x800 - 0x7d4 - sizeof(Sub_t)];
    int unk_800;
} Obj_t;

void func_ov003_0220fb94(Obj_t *self)
{
    Sub_t *sub = &self->sub;
    int arr[3];
    int arg0, arg1;

    func_ov003_0220fcb4(self);

    arr[0] = sub->b;
    arr[1] = sub->c;
    arr[2] = sub->d;
    if (func_0200f434(self, arr)) {
        func_ov003_0220fc88(self);
    }

    func_02010d64(self);

    arg0 = data_020ccf94;
    arg1 = self->unk_800;
    if (func_02073908(arg0, arg1)) {
        func_ov003_0220fc34(self);
    } else {
        func_ov003_0220fbf8(self);
    }
}
