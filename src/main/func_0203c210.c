/* func_0203c210 @ 0x0203c210, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203caa4(void *p, int a, int b);

typedef struct {
    unsigned int words[3];
} Source;

typedef struct {
    char pad_00[0x14];
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Dest;

void func_0203c210(char *r0, Dest *r1, Source *r2)
{
    Dest *r5 = r1;
    if (r5 == 0) {
        r5 = (Dest *) (r0 + 0xfc);
    }
    func_0203caa4(r0, 0xb, 0);
    r5->a = r2->words[0];
    r5->b = r2->words[1];
    r5->c = r2->words[2];
}
