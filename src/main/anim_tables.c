/* anim_tables: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205cf28 @ 0x0205cf28, 0xc bytes, Thumb
 * func_0205cf1c @ 0x0205cf1c, 0xc bytes, Thumb
 * func_0205cf10 @ 0x0205cf10, 0xc bytes, Thumb
 * func_0205ceec @ 0x0205ceec, 0x24 bytes, Thumb
 * func_0205cec8 @ 0x0205cec8, 0x24 bytes, Thumb
 * func_0205cebc @ 0x0205cebc, 0xc bytes, Thumb
 * func_0205ceb0 @ 0x0205ceb0, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char lo;
    unsigned char hi;
} pair_t;

extern unsigned short data_020cc14c[];
extern unsigned short data_020cc3d4[];
extern unsigned char data_020dd410[];
extern unsigned char data_020dd414[];
extern unsigned short data_020dd424[];
extern unsigned char data_020cc008[];

unsigned short func_0205cf28(unsigned int index)
{
    return data_020cc14c[index];
}

unsigned short func_0205cf1c(unsigned int index)
{
    return data_020cc3d4[index];
}

unsigned char func_0205cf10(unsigned int r0)
{
    return data_020dd410[r0];
}

unsigned char func_0205ceec(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    func_0205cf10(r0);
    {
        unsigned char *r1 = *(unsigned char **) (data_020dd414 + (r5 << 2));
        return r1[r4 << 1];
    }
}

unsigned char func_0205cec8(int a, int b)
{
    func_0205cf10(a);
    return ((pair_t * *) data_020dd414)[a][b].hi;
}

unsigned short func_0205cebc(unsigned int r0)
{
    return data_020dd424[r0];
}

unsigned char func_0205ceb0(unsigned int r0)
{
    return data_020cc008[r0];
}
