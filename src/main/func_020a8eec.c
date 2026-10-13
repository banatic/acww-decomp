/* func_020a8eec @ 0x020a8eec, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[128];
    unsigned long unk_80;
} UnkStruct_020a8eec;
void func_020a8eec(UnkStruct_020a8eec *p, unsigned long v)
{
    p->unk_80 = v;
}
