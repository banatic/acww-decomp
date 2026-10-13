/* func_ov003_02215f58 @ 0x02215f58, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_02010f5c(void *);
extern void func_02010d64(void *);
extern int func_02073908(int, int);
extern void func_ov003_02215fd8(void *);
extern int func_02008258(void *, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
    int unk_800;
} UnkStruct_02215f58;

void func_ov003_02215f58(UnkStruct_02215f58 *p)
{
    func_02010f5c(p);
    func_02010d64(p);
    if (func_02073908(data_020ccf94, p->unk_800) != 0) {
        func_ov003_02215fd8(p);
    } else {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
    }
}
