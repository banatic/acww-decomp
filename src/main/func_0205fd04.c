/* func_0205fd04 @ 0x0205fd04, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8];
    char unk_08;
    char pad_09[0x14 - 0x9];
    int unk_14;
    char unk_18;
    char pad_19[0x1c - 0x19];
    int unk_1C;
    int unk_20;
    int unk_24;
} Param;

extern int func_0205fb28(int *vec, int a, void *b, void *c);
extern void func_0206026c(Param *param, int a);

void func_0205fd04(Param *param)
{
    struct {
        int flag;
        int vec[3];
    } local;

    local.vec[0] = param->unk_1C;
    local.vec[1] = param->unk_20;
    local.vec[2] = param->unk_24;
    local.flag = 1;
    if (func_0205fb28(local.vec, param->unk_14, &param->unk_08, &param->unk_18) != 0) {
        func_0206026c(param, 1);
    }
}
