/* func_ov133_0229ad10 @ 0x0229ad10, 0x58 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov133_0229c908;
extern void func_ov002_0220ba0c(void *addr);
extern void func_ov002_0220afdc(void *addr);
extern void func_ov002_02209cb4(void *addr);
extern void func_02138c48(void *addr, int a, int b, void (*cb)(void));
extern void func_ov002_0220826c(void *addr);
extern void func_ov002_02207f6c(void *addr);
extern void func_02070be8(void);

typedef struct {
    void *unk_00;         // offset 0x00
    char pad_04[0xac];    // 0x04..0xaf
    char unk_B0;          // 0xb0
    char pad_B1[0x6b];    // 0xb1..0x11b
    char unk_11C;         // 0x11c
    char pad_11D[0x63];   // 0x11d..0x17f
    char unk_180;         // 0x180
    char pad_181[0x1213]; // 0x181..0x1393
    char unk_1394;        // 0x1394
} UnkStruct_0229ad10;

UnkStruct_0229ad10 *func_ov133_0229ad10(UnkStruct_0229ad10 *obj)
{
    obj->unk_00 = &data_ov133_0229c908;
    func_ov002_0220ba0c(&obj->unk_1394);
    func_ov002_0220afdc(&obj->unk_180);
    func_ov002_02209cb4(&obj->unk_11C);
    func_02138c48(&obj->unk_B0, 1, 0x6c, func_02070be8);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
