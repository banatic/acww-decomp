/* func_02046154 @ 0x02046154, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_02046154;

typedef struct {
    unsigned char lo : 3;
    unsigned char field : 5;
} UnkField;

extern int func_02045cec(UnkStruct_02046154 *p, int flag);
extern UnkField *func_02045bac(int id);
extern void func_02045eec(int id);

int func_02046154(UnkStruct_02046154 *arg)
{
    UnkStruct_02046154 local;
    int ret;
    int result = 1;

    local.a = arg->a;
    local.b = arg->b;
    ret = func_02045cec(&local, 0);
    if (ret >= 0) {
        UnkField *uf = func_02045bac(ret);
        if (uf->field == 0x1A) {
            func_02045eec(ret);
        } else {
            result = 0;
        }
    }
    return result;
}
