/* func_02064170 @ 0x02064170, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *arg);
extern int data_020de67c;

typedef struct {
    int *unk_00;
} UnkStruct_02064170;

UnkStruct_02064170 *func_02064170(UnkStruct_02064170 *arg)
{
    func_020a88ec(arg);
    arg->unk_00 = &data_020de67c;
    return arg;
}
