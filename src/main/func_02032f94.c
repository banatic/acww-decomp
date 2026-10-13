/* func_02032f94 @ 0x02032f94, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *arg1, unsigned int arg2, unsigned int arg3, void *arg4, void *arg5);
extern void func_020330e8(void);
extern void func_02033100(void);

typedef struct {
    int unk_00;
    char unk_04;
} UnkStruct_02032f94;

UnkStruct_02032f94 *func_02032f94(UnkStruct_02032f94 *obj)
{
    func_02138d6c(&obj->unk_04, 0x10, 0x24, (void *) func_02033100, (void *) func_020330e8);
    obj->unk_00 = 0;
    return obj;
}
