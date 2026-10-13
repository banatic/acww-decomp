/* func_020c1538 @ 0x020c1538, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *obj);

typedef struct {
    volatile void *unk_00;
    unsigned char pad_04[0x4C];
    volatile void *unk_50;
} UnkStruct_020c1538;

extern unsigned char data_020da13c[];
extern unsigned char data_020e69a4[];
extern unsigned char data_0213efe8[];
extern unsigned char data_0213f004[];

void *func_020c1538(void)
{
    void *mem;
    UnkStruct_020c1538 *obj;

    mem = func_020edf70(0x60);
    obj = (UnkStruct_020c1538 *) mem;
    if (obj) {
        func_020ee660(obj);
        obj->unk_00 = (void *) data_020da13c;
        obj->unk_00 = (void *) data_020e69a4;
        obj->unk_50 = (void *) data_0213efe8;
        obj->unk_50 = (void *) data_0213f004;
    }
    return obj;
}
