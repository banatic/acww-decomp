/* spawner_9: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02085f04 @ 0x02085f04, 0x2 bytes, Thumb
 * func_02085ed0 @ 0x02085ed0, 0x34 bytes, Thumb
 */

struct UnkStruct_02085ed0 {
    void *volatile unk_00;
    char pad_04[0x4C];
    char unk_50;
};

extern char data_020da13c;
extern char data_020e1cc0;
extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);
extern void func_02084f88(void *data);

void func_02085f04(void *object) {}

void *func_02085ed0(void)
{
    struct UnkStruct_02085ed0 *obj;
    obj = (struct UnkStruct_02085ed0 *) func_020edf70(0x78);
    if (obj) {
        func_020ee660(obj);
        obj->unk_00 = &data_020da13c;
        obj->unk_00 = &data_020e1cc0;
        func_02084f88(&obj->unk_50);
    }
    return obj;
}
