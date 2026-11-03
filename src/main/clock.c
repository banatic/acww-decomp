/* clock: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209dbbc @ 0x0209dbbc, 0x28 bytes, Thumb
 * func_0209dbb4 @ 0x0209dbb4, 0x8 bytes, Thumb
 * func_0209db78 @ 0x0209db78, 0x3c bytes, Thumb
 * func_0209db50 @ 0x0209db50, 0x26 bytes, Thumb
 */

typedef struct {
    int unk_00;
    short unk_04;
} UnkStruct_0209dbb4;

extern unsigned char data_021dc744[];
extern unsigned char data_021dc754[];
extern void func_0209df04(unsigned long long *out);
extern int func_0209e350(unsigned long long *a, unsigned long long *b);

unsigned int func_0209dbbc(void)
{
    unsigned int *base = (unsigned int *) data_021dc754;
    unsigned int *other = (unsigned int *) data_021dc744;
    return base[1] | ((other[2] << 8) | ((base[2] << 24) | (base[0] << 16)));
}

void func_0209dbb4(UnkStruct_0209dbb4 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
}

int func_0209db78(int unused, unsigned long long *p)
{
    unsigned long long local = 0;

    func_0209df04(&local);
    if (local < *p) {
        return func_0209e350(&local, p);
    } else {
        return -func_0209e350(p, &local);
    }
}

int func_0209db50(int unused, unsigned char *b)
{
    unsigned int buf[2];
    buf[0] = 0;
    buf[1] = 0;
    func_0209df04((unsigned long long *) (&buf));
    return (short) (*b - ((unsigned char *) buf)[0]);
}
