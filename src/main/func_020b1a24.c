/* func_020b1a24 @ 0x020b1a24, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1E];
    char someData[0x0C];
    unsigned short array[16];
} UnkStruct_020b1a24;
extern void func_02051bf8(void *ptr, int value);
extern void func_02095238(void *ptr);

void func_020b1a24(UnkStruct_020b1a24 *p)
{
    int i;
    for (i = 0; i < 16; i++) {
        p->array[i] = 0xFFFF;
    }
    func_02051bf8(p->someData, 6);
    func_02095238(p);
}
