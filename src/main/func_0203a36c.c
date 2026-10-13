/* func_0203a36c @ 0x0203a36c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
} UnkStruct_0203a36c;

extern unsigned int data_020da628;
extern void func_020a887c(UnkStruct_0203a36c *);
extern void func_020edb3c(UnkStruct_0203a36c *);

UnkStruct_0203a36c *func_0203a36c(UnkStruct_0203a36c *obj)
{
    obj->unk_00 = (unsigned int) &data_020da628;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}
