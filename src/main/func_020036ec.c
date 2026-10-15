/* func_020036ec @ 0x020036ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[14];
    unsigned char unk_0E;
    unsigned char unk_0F;
} UnkStruct_020036ec;

extern char data_021dc7aa[];
extern void func_020642d0(void *s, void *ptr);

void func_020036ec(UnkStruct_020036ec *s, unsigned char byte_F, unsigned char byte_E, void *ptr)
{
    s->unk_0F = byte_F;
    s->unk_0E = byte_E;
    if (ptr == 0) {
        ptr = data_021dc7aa;
    }
    func_020642d0(s, ptr);
}
