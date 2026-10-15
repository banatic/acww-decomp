/* func_ov003_02215bf8 @ 0x02215bf8, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215c84(void *);
extern int func_0200f554(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_020113a4(int, int, int);
extern void func_0201107c(void *, int *);
extern void func_ov003_02215c44(void *);

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_02215bf8;

void func_ov003_02215bf8(UnkStruct_02215bf8 *ptr)
{
    int local;
    func_ov003_02215c84(ptr);
    if (func_0200f554(ptr) != 0) {
        func_0201100c(ptr);
    }
    func_02010d64(ptr);
    local = func_020113a4(ptr->unk_98, 0, 0x171);
    func_0201107c(ptr, &local);
    func_ov003_02215c44(ptr);
}
