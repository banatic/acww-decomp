/* overlay_slots_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204fa5c @ 0x0204fa5c, 0xc bytes, Thumb
 * func_0204fa54 @ 0x0204fa54, 0x8 bytes, Thumb
 * func_0204fa4c @ 0x0204fa4c, 0x8 bytes, Thumb
 * func_0204fa18 @ 0x0204fa18, 0x32 bytes, Thumb
 * func_0204f9ec @ 0x0204f9ec, 0x2c bytes, Thumb
 */

typedef struct Dest {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    int unk_04;
    int unk_08;
} Dest;

struct UnkStruct_0204f9ec {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern int FS_LoadOverlayInfo(int, int, int);
extern void func_0206464c(int);
extern void func_02064640(int);

void func_0204fa5c(int p0, int p1)
{
    FS_LoadOverlayInfo(p0, 0, p1);
}

void func_0204fa54(int argument0)
{
    func_0206464c((int) argument0);
}

void func_0204fa4c(int argument0)
{
    func_02064640((int) argument0);
}

void func_0204fa18(Dest *dest, int param2)
{
    int buffer[11];
    func_0204fa5c((int) buffer, param2);
    func_0204fa54(param2);
    dest->unk_00 = (unsigned char) param2;
    dest->unk_01 = 1;
    dest->unk_02 = 0;
    dest->unk_04 = buffer[1];
    dest->unk_08 = buffer[2] + buffer[3];
}

void func_0204f9ec(struct UnkStruct_0204f9ec *p)
{
    unsigned char c;
    char buffer[44];
    c = p->unk_00;
    func_0204fa4c((unsigned char) c);
    func_0204fa5c((int) buffer, (unsigned char) c);
    p->unk_00 = 0xFF;
    p->unk_01 = 0;
    p->unk_02 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
}
