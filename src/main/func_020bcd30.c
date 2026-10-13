/* func_020bcd30 @ 0x020bcd30, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f34];
    volatile int unk_2F34;
} UnkStruct_020bcd30;

extern int func_020644cc(int);
extern int func_020bce60(UnkStruct_020bcd30 *, int);
extern void func_020bcda0(UnkStruct_020bcd30 *, int, int, int);
extern void func_020bcd7c(UnkStruct_020bcd30 *, volatile int *);

void func_020bcd30(UnkStruct_020bcd30 *obj)
{
    int v;
    obj->unk_2F34 = obj->unk_2F34 - 1;
    if (obj->unk_2F34 > 0) {
        return;
    }
    v = func_020644cc(4);
    if (func_020bce60(obj, v)) {
        func_020bcda0(obj, v, 1, 0);
        func_020bcd7c(obj, &obj->unk_2F34);
    }
}
