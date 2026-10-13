/* func_02093714 @ 0x02093714, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *, void *, int, int);
extern void func_0203423c(void *);
extern int func_02094cf8(int, void *, void *, int, void *, int);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;

typedef struct {
    unsigned char pad_00[0x34];
    int type;
    unsigned char pad_38[0xc];
} UnkStruct_02093714;

int func_02093714(void *a, void *b, int arg_c, void *d)
{
    int c = arg_c;
    int result;
    UnkStruct_02093714 local;
    int type;
    unsigned int cond;

    func_02034270(&local, b, 0, 0);
    type = local.type;
    result = 3;
    cond = (data_020e54a8 == 1) ? 1 : 0;

    if (cond > 0) {
        if (type == 9 || type == 3) {
            result = func_02094cf8(0x4b, a, b, c, d, 0);
        }
    } else {
        if (type == 0x16 || func_020ba4e4() == 1) {
            result = func_02094cf8(0x4d, a, b, c, d, 0);
        } else if (type == 3 && func_020b6598() != 0) {
            result = func_02094cf8(0x4e, a, b, c, d, 0);
        } else {
            result = func_02094cf8((type == 0x13) ? 0x4c : 0x4b, a, b, c, d, 0);
        }
    }

    func_0203423c(&local);
    return result;
}
