/* func_020b9e58 @ 0x020b9e58, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1cc(void *obj);
extern void func_020ba1b0(void *obj);
extern char data_020e591c[];

typedef struct {
    char pad[12];
} SubObject;

typedef struct {
    void *unk_00;
    char pad[12];
    SubObject sub1;
    SubObject sub2;
} UnkStruct_020b9e58;

UnkStruct_020b9e58 *func_020b9e58(UnkStruct_020b9e58 *obj)
{
    func_020ba1cc(obj);
    obj->unk_00 = data_020e591c;
    func_020ba1b0(&obj->sub1);
    func_020ba1b0(&obj->sub2);
    return obj;
}
