/* func_020b64f0 @ 0x020b64f0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct In {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} In;

typedef struct UnkStruct_020b64f0 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    short e;
    unsigned char unk_12;
    unsigned char g;
    unsigned char h;
} UnkStruct_020b64f0;

void func_020b64f0(UnkStruct_020b64f0 *out, unsigned char b, In *in, unsigned int d, short e, unsigned int f, unsigned int g)
{
    out->unk_12 = b;
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    out->d = d;
    out->e = e;
    out->g = (unsigned char) f;
    out->h = (unsigned char) g;
}
