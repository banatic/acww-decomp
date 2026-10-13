/* func_020871dc @ 0x020871dc, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short v[6];
} UnkStruct_020871dc;
typedef struct {
    unsigned short unk_00;
    UnkStruct_020871dc a1;
    unsigned short unk_0E;
    UnkStruct_020871dc a2;
    signed char unk_1C;
    unsigned char unk_1D;
} UnkStruct_020871dc_2;
void func_020871dc(UnkStruct_020871dc_2 *d, UnkStruct_020871dc_2 *s)
{
    d->unk_00 = s->unk_00;
    d->a1 = s->a1;
    d->unk_0E = s->unk_0E;
    d->a2 = s->a2;
    d->unk_1C = s->unk_1C;
    d->unk_1D = s->unk_1D;
}
