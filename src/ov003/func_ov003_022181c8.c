/* func_ov003_022181c8 @ 0x022181c8, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022181c8 {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8f0 - 0x7f0 - 4];
    char sub_8f0[0xc84 - 0x8f0];
    short unk_C84;
} UnkStruct_022181c8;

extern void func_ov003_02218330(void *p, unsigned char *a, unsigned char *b);
extern int func_ov003_02218344(void *s, unsigned char a, unsigned char b, int c, int d);

void func_ov003_022181c8(UnkStruct_022181c8 *s, int v)
{
    if (s->unk_7F0 == 59) {
        s->unk_C84 = v;
    } else {
        unsigned char buf[2];
        func_ov003_02218330(&s->sub_8f0[0], &buf[0], &buf[1]);
        func_ov003_02218344(s, buf[0], buf[1], 6, v);
    }
}
