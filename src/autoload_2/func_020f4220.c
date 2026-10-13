/* func_020f4220 @ 0x020f4220, 0xf4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// Sound setup: a 4-byte record is passed by value; the volatile read makes a fresh copy for it.
typedef struct UnkStruct_020f4220 {
    unsigned char unk_00, unk_01, unk_02, unk_03;
} UnkStruct_020f4220;
extern UnkStruct_020f4220 data_0213e990;
extern struct UnkStruct_020f4220_2 {
    unsigned char pad_00[0x15];
    UnkStruct_020f4220 unk_15;
} data_021fd054;
extern struct UnkStruct_020f4220_3 {
    unsigned char pad_00[0x62];
    unsigned char unk_62;
} data_021fd1bc;
extern int func_020eef70(int);
extern void func_020f2344(struct UnkStruct_020f4220_3 *);
extern void NNS_SndPlayerCreateHeap(int, int, int);
extern void NNS_SndHeapSaveState(int);
extern void func_020ef040(struct UnkStruct_020f4220_2 *, int, int, UnkStruct_020f4220);
extern void func_020f59b4(void);

void func_020f4220(int a0, int a1, unsigned char a2)
{
    int h;
    UnkStruct_020f4220 t;

    h = func_020eef70(a0);
    if (data_021fd1bc.unk_62 == 0) {
        func_020f2344(&data_021fd1bc);
        NNS_SndPlayerCreateHeap(0, h, a1);
        NNS_SndHeapSaveState(h);
    }
    t = data_0213e990;
    t.unk_00 = a2;
    data_021fd054.unk_15 = t;
    func_020ef040(&data_021fd054, 0, 0, *(volatile UnkStruct_020f4220 *) &t);
    func_020f59b4();
    NNS_SndHeapSaveState(h);
}
