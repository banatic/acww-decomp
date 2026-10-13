/* func_020762b8 @ 0x020762b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a76cc(void *);
extern void func_020a7684(void *, void *, void *, void *);
extern void func_020a76c8(void *);
extern void func_020736bc(void *, void *, int);
extern void func_020a6f20(int, int);
extern void func_020a6f10(int);
extern void func_020a6f34(int);

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_020762b8;

extern UnkStruct_020762b8 *data_020ccf94;

void func_020762b8(int a, int b, int c, int param)
{
    int local[5];
    UnkStruct_020762b8 *s;

    func_020a76cc(local);
    s = data_020ccf94;
    func_020736bc(s, local, 1);
    func_020a7684(local, &local[1], &local[2], &local[3]);

    if (param == 0) {
        func_020a6f20(s->unk_64, local[1]);
    } else {
        func_020a6f20(param, local[1]);
    }

    if (local[2] < 4) {
        func_020a6f10(local[2]);
    }
    if (local[3] < 4) {
        func_020a6f34(local[3]);
    }

    func_020a76c8(local);
}
