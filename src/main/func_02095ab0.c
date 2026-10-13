/* func_02095ab0 @ 0x02095ab0, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(void *);
extern int func_02009a44(int, void *, int, int, int);

struct UnkStruct_02095ab0 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

int func_02095ab0(struct UnkStruct_02095ab0 *p, int arg2, void *arg3)
{
    int result;
    struct UnkStruct_02095ab0 local;

    result = func_02096718(arg3);
    if (result != 0) {
        local.unk_00 = p->unk_00;
        local.unk_04 = p->unk_04;
        local.unk_08 = p->unk_08;
        result = func_02009a44(result, &local, arg2, 5, -1);
    } else {
        result = 0;
    }
    return result;
}
