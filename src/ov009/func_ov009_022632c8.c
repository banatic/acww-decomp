/* func_ov009_022632c8 @ 0x022632c8, 0x4c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_022646b8(void *p, int v);
extern void func_0205510c(void *p, int v);
extern void func_ov009_022645b8(void *p, void *s);

typedef struct {
    long long unk_00;
    long long unk_08;
    long long unk_10;
    long long unk_18;
    long long unk_20;
    long long unk_28;
} UnkStruct_022632c8;

void func_ov009_022632c8(void *p)
{
    if (*(int *) ((char *) p + 0x198) != 0) {
        UnkStruct_022632c8 local;
        func_ov009_022646b8(p, 0);
        func_0205510c((char *) p + 0x13c, 0);
        local = *(UnkStruct_022632c8 *) ((char *) p + 0x1a0);
        func_ov009_022645b8(p, &local);
    }
}
