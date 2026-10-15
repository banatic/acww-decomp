/* func_0202de9c @ 0x0202de9c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020161ac(void *);

typedef struct UnkStruct_0202de9c {
    void *unk_00;
    unsigned char pad_04[0x124 - 4];
    unsigned short unk_124;
    unsigned char pad_126[0x19c - 0x124 - 2];
    unsigned short unk_19C;
} UnkStruct_0202de9c;

extern unsigned char data_020d9df8[];

UnkStruct_0202de9c *func_0202de9c(UnkStruct_0202de9c *obj)
{
    func_020161ac(obj);
    obj->unk_00 = (void *) data_020d9df8;
    obj->unk_124 = 0xfff1;
    obj->unk_19C = 0xfff1;
    return obj;
}
