/* func_0204fa18 @ 0x0204fa18, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204fa5c(int *ptr);
extern void func_0204fa54(int value);

typedef struct Dest {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    int unk_04;
    int unk_08;
} Dest;

void func_0204fa18(Dest *dest, int param2)
{
    int buffer[11];
    func_0204fa5c(buffer);
    func_0204fa54(param2);
    dest->unk_00 = (unsigned char) param2;
    dest->unk_01 = 1;
    dest->unk_02 = 0;
    dest->unk_04 = buffer[1];
    dest->unk_08 = buffer[2] + buffer[3];
}
