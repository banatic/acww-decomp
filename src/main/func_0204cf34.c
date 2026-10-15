/* func_0204cf34 @ 0x0204cf34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile unsigned int unk_00;
} UnkStruct_0204cf34;

extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020db898[];

void *func_0204cf34(void *ptr)
{
    UnkStruct_0204cf34 *s = (UnkStruct_0204cf34 *) ptr;
    s->unk_00 = (unsigned int) data_020db898;
    s->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    func_020edf54(ptr);
    return ptr;
}
