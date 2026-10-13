/* func_0203f0f8 @ 0x0203f0f8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void func_020e8ce0(int, void *);
extern __arm void func_020ee62c(void *);

typedef struct {
    unsigned int unk_00;
    char pad_04[0x4c];
    char sub;
} UnkStruct_0203f0f8;

extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];
extern unsigned char data_020dab34[];
extern unsigned char data_0213ff78[];

void *func_0203f0f8(UnkStruct_0203f0f8 *obj)
{
    obj->unk_00 = (unsigned int) data_020dab34;
    obj->unk_00 = (unsigned int) data_020d7244;
    func_020e8ce0((unsigned int) data_0213ff78, &obj->sub);
    obj->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
