/* func_ov003_02221054 @ 0x02221054, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0223cfe4;
int func_ov003_022213f8(void *p, void *a, void *b, void *c, int d, unsigned int e, int f, int g);

typedef struct {
    unsigned int a, b;
} UnkStruct_02221054;
typedef struct {
    unsigned int a, b, c;
} UnkStruct_02221054_2;

void func_ov003_02221054(void *arg1, unsigned int arg2, UnkStruct_02221054 *arg3, UnkStruct_02221054_2 *arg4)
{
    UnkStruct_02221054 local2;
    UnkStruct_02221054_2 local3;
    local3.a = arg4->a;
    local3.b = arg4->b;
    local3.c = arg4->c;
    local2.a = arg3->a;
    local2.b = arg3->b;
    func_ov003_022213f8(&data_ov003_0223cfe4, arg1, &local2, &local3, 7, arg2, 0, 0);
}
