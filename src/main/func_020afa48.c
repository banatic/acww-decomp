/* func_020afa48 @ 0x020afa48, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020afa48 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};
struct Stack {
    volatile struct UnkStruct_020afa48 t;
    unsigned char rest[8];
};
extern void *func_020afad4(void *p);
extern void func_0209e140(void *p, int n);

struct UnkStruct_020afa48 func_020afa48(void *a)
{
    struct Stack s;

    s.t.unk_03 = 0;
    s.t.unk_00 = s.t.unk_03;
    s.t.unk_01 = s.t.unk_00;
    s.t.unk_02 = s.t.unk_01;
    if (((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_03 != 0) {
        *(unsigned int *) &s.rest[0] = 0;
        *(unsigned int *) &s.rest[4] = 0;
        s.rest[5] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_02;
        s.rest[4] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_01;
        s.rest[3] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_00;
        s.rest[2] = 6;
        s.rest[1] = 0;
        s.rest[0] = 0;
        *(unsigned short *) &s.rest[6] = 0;
        func_0209e140(&s.rest[0], 1);
        s.t.unk_02 = s.rest[5];
        s.t.unk_01 = s.rest[4];
        s.t.unk_00 = s.rest[3];
    }
    return s.t;
}
