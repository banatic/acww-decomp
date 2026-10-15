/* func_0200316c @ 0x0200316c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ce0(void *arg0, void *arg1);
extern void func_020ee62c(void *arg0);

typedef struct UnkStruct_0200316c {
    void *vtable;
    char pad_04[0x4C];
    void *unk_50;
} UnkStruct_0200316c;

extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];
extern unsigned char data_0213ff78[];

UnkStruct_0200316c *func_0200316c(UnkStruct_0200316c *obj)
{
    obj->vtable = (void *) data_020d7244;
    func_020e8ce0((void *) data_0213ff78, (void *) &obj->unk_50);
    obj->vtable = (void *) data_020da13c;
    func_020ee62c((void *) obj);
    return obj;
}
