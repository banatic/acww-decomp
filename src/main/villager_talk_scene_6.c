/* villager_talk_scene_6: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202decc @ 0x0202decc, 0x30 bytes, Thumb
 * func_0202de9c @ 0x0202de9c, 0x30 bytes, Thumb
 * func_0202de84 @ 0x0202de84, 0x18 bytes, Thumb
 * func_0202de64 @ 0x0202de64, 0x20 bytes, Thumb
 * func_0202de4c @ 0x0202de4c, 0x18 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[288];
    unsigned short unk_124;
    char pad_126[118];
    unsigned short unk_19C;
} UnkStruct_0202decc;

typedef struct UnkStruct_0202de9c {
    void *unk_00;
    unsigned char pad_04[0x124 - 4];
    unsigned short unk_124;
    unsigned char pad_126[0x19c - 0x124 - 2];
    unsigned short unk_19C;
} UnkStruct_0202de9c;

struct UnkStruct_0202de84 {
    void *unk_00;
};

struct UnkStruct_0202de64 {
    void *unk_00;
};

extern void *func_020161ac(void *p);
extern unsigned char data_020d9df8[];
extern void *func_0201615c(struct UnkStruct_0202de84 *);
void func_020edb3c(struct UnkStruct_0202de64 *obj);

void *func_0202decc(UnkStruct_0202decc *ptr)
{
    func_020161ac(ptr);
    ptr->unk_00 = ((char *) data_020d9df8);
    ptr->unk_124 = 0xfff1;
    ptr->unk_19C = 0xfff1;
    return ptr;
}

UnkStruct_0202de9c *func_0202de9c(UnkStruct_0202de9c *obj)
{
    func_020161ac(obj);
    obj->unk_00 = (void *) data_020d9df8;
    obj->unk_124 = 0xfff1;
    obj->unk_19C = 0xfff1;
    return obj;
}

struct UnkStruct_0202de84 *func_0202de84(struct UnkStruct_0202de84 *obj)
{
    obj->unk_00 = (void *) data_020d9df8;
    func_0201615c(obj);
    return obj;
}

struct UnkStruct_0202de64 *func_0202de64(struct UnkStruct_0202de64 *obj)
{
    obj->unk_00 = ((char *) data_020d9df8);
    func_0201615c((struct UnkStruct_0202de84 *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_0202de4c(void *ptr)
{
    *(void **) ptr = ((char *) data_020d9df8);
    func_0201615c((struct UnkStruct_0202de84 *) ptr);
    return ptr;
}
