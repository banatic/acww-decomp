/* func_02095578 @ 0x02095578, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984fc(void *);
extern void func_02099740(void *, int);
extern void *func_02096718(void *);
extern char *func_0209984c(void *);
extern void func_0205dc94(void *, void *);

typedef struct {
    char pad_00[0x704];
    int unk_704;
    char pad_708[0x5];
    char unk_70D;
} UnkStruct_02095578;

int func_02095578(int a, void *b)
{
    void *ptr;
    UnkStruct_02095578 *info;
    char *tmp;

    ptr = func_020984fc(b);
    if (ptr == 0) {
        return 0;
    }
    func_02099740(ptr, a);
    info = (UnkStruct_02095578 *) func_02096718(b);
    if (info == 0) {
        return 0;
    }
    if (info->unk_704 >= 0xa1) {
        return 0;
    }
    if (a) {
        tmp = func_0209984c(ptr) + 0x10;
    } else {
        tmp = func_0209984c(ptr);
    }
    func_0205dc94(&info->unk_70D, tmp);
    return 1;
}
