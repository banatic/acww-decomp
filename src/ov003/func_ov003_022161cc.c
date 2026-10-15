/* func_ov003_022161cc @ 0x022161cc, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int arr[12];
} BigStruct;
typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
} Header;
typedef struct {
    unsigned char pad_00[0x2d0];
    unsigned char sub_2d0[8];
    unsigned int unk_2D8;
    unsigned char pad_2DC[0x668 - 0x2dc];
    BigStruct unk_668;
    unsigned char pad_698[0x7d4 - (0x668 + 0x30)];
    Header header;
} UnkStruct_022161cc;
extern void func_02010f5c(int argument0);
extern int func_02056f28(void *p, int a);
extern void func_0200f268(UnkStruct_022161cc *obj, int a);
extern int func_0200f328(UnkStruct_022161cc *obj, int a);
extern unsigned int *func_0200f27c(UnkStruct_022161cc *obj, int a);
extern void func_02045f08(int *p, int a);
extern int func_0203f7d0(int *a, int *b);
extern int func_02091254(int a, int *b, int c, int d);
extern void MTX_MultVec43(int *a, int *b, int *c);
extern int func_0200faf0(UnkStruct_022161cc *obj, int a);
void func_ov003_022161cc(UnkStruct_022161cc *obj)
{
    int header_tmp[2];
    BigStruct localA;
    int vec[3];
    BigStruct localB;
    int t[3];
    int out[3];
    Header *h;
    int v0;
    int v1;
    int v2;
    unsigned char t0;
    unsigned char t1;
    func_02010f5c((int) obj);
    if (((obj->unk_2D8 << 4) >> 16) < 8) {
        return;
    }
    if (func_02056f28(obj->sub_2d0, 8) != 0) {
        h = &obj->header;
        if (h->unk_02) {
            t0 = h->unk_00;
            t1 = h->unk_01;
            header_tmp[0] = t0;
            header_tmp[1] = t1;
            func_02045f08(header_tmp, 0);
            func_0200f268(obj, 0x12);
            h->unk_02 = 0;
        }
        func_0200f328(obj, 0x840);
        func_0200f268(obj, 0);
        func_0200f27c(obj, 9);
        localA = obj->unk_668;
        vec[0] = v0 = localA.arr[9];
        vec[1] = v1 = localA.arr[10];
        vec[2] = v2 = localA.arr[11];
        func_0203f7d0(vec, vec);
        func_02091254(0x8c, vec, 0, 0);
        vec[0] = v0;
        vec[1] = v1;
        vec[2] = v2;
        localA.arr[11] = 0;
        localA.arr[10] = 0;
        localA.arr[9] = 0;
        localB = localA;
        t[1] = 0;
        t[0] = 0;
        t[2] = 0xab8;
        MTX_MultVec43(t, localB.arr, out);
        vec[0] += out[0];
        vec[1] += out[1];
        vec[2] += out[2];
        func_0203f7d0(vec, vec);
        func_02091254(0x8b, vec, 0, 0);
    }
    func_0200faf0(obj, 0x200);
}
