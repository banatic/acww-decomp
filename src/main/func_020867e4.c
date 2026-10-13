/* func_020867e4 @ 0x020867e4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020867e4 {
    unsigned short v[6];
} UnkStruct_020867e4;

typedef struct UnkStruct_020867e4_2 {
    unsigned short unk_00;
    UnkStruct_020867e4 unk_02;
    unsigned short unk_0E;
    UnkStruct_020867e4 unk_10;
    signed char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E[4];
} UnkStruct_020867e4_2;

extern void func_02003738(void *);

void func_020867e4(UnkStruct_020867e4_2 *d, UnkStruct_020867e4_2 *s)
{
    d->unk_00 = s->unk_00;
    d->unk_02 = s->unk_02;
    d->unk_0E = s->unk_0E;
    d->unk_10 = s->unk_10;
    d->unk_1C = s->unk_1C;
    d->unk_1D = s->unk_1D;
    func_02003738(&d->unk_1E);
}
