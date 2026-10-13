/* func_020a9d88 @ 0x020a9d88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aa79c(void *);
extern void func_020aa28c(void *);

typedef struct {
    char data[0xC4];
} SubA;
typedef struct {
    char data[0x19C];
} SubB;

struct UnkStruct_020a9d88 {
    int unk_00;
    SubA a;
    SubB b;
    char unk_264;
};

struct UnkStruct_020a9d88 *func_020a9d88(struct UnkStruct_020a9d88 *param)
{
    param->unk_00 = 0;
    func_020aa79c(&param->a);
    func_020aa28c(&param->b);
    param->unk_264 = 0;
    return param;
}
