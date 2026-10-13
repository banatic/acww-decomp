/* func_020afc84 @ 0x020afc84, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020afad4(unsigned char *p);
extern unsigned char data_021f395c;

struct UnkStruct_020afc84 {
    unsigned char a, b, c, d, e, unk_05;
    unsigned short g;
};

int func_020afc84(struct UnkStruct_020afc84 *out)
{
    unsigned char *base = &data_021f395c;
    if (func_020afad4(base)[3] != 0) {
        out->unk_05 = func_020afad4(base)[2];
        out->e = func_020afad4(base)[1];
        out->d = func_020afad4(base)[0];
        out->c = 6;
        out->b = 0;
        out->a = 0;
        out->g = 0;
        return 1;
    } else {
        return 0;
    }
}
