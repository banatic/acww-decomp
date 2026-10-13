/* func_0208fe80 @ 0x0208fe80, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern unsigned char data_020e246c;

typedef struct {
    void *unk_00;
    char pad_04[8];
    unsigned int unk_0C;
    unsigned int unk_10;
    char unk_14[0x14];
    char unk_28;
} UnkStruct_0208fe80;

void *func_0208fe80(void *obj)
{
    UnkStruct_0208fe80 *s = (UnkStruct_0208fe80 *) obj;
    func_0208af30(s);
    s->unk_00 = &data_020e246c;
    s->unk_0C = 0;
    s->unk_10 = 0;
    func_0208a1f8(s->unk_14);
    s->unk_28 = 0;
    return s;
}
