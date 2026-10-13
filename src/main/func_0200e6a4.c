/* func_0200e6a4 @ 0x0200e6a4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200e6a4 UnkStruct_0200e6a4;
struct UnkStruct_0200e6a4 {
    char pad_00[0x428];
    char pad_428[0x3D8];
    unsigned int value;
};

extern unsigned char data_020c75e4[];
extern int func_020961d0(unsigned int);
extern void func_0205e4e8(void *, unsigned char);
extern void func_020112f8(unsigned short *, UnkStruct_0200e6a4 *);
extern int func_020112e4(UnkStruct_0200e6a4 *);
extern int func_020112d0(UnkStruct_0200e6a4 *);
extern void func_020100e8(UnkStruct_0200e6a4 *, unsigned short *, int, int, int);

void func_0200e6a4(UnkStruct_0200e6a4 *obj)
{
    unsigned short s1;
    unsigned short s2;
    int idx;
    idx = func_020961d0(obj->value);
    func_0205e4e8((char *) obj + 0x428, data_020c75e4[idx]);
    func_020112f8(&s2, obj);
    s1 = s2;
    func_020100e8(obj, &s1, func_020112e4(obj), func_020112d0(obj), 1);
}
