/* func_02018b60 @ 0x02018b60, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02018b60 {
  public:
    virtual int d0();
    virtual int d1();
    virtual int d2();
    virtual int d3();
    virtual int d4();
    virtual int d5();
    virtual int d6();
    virtual int d7();
    virtual int d8();
    virtual int d9();
    virtual int d10();
    virtual int d11();
    virtual int d12();
    virtual int d13();
    virtual int d14();
    virtual int d15();
    virtual int d16();
    virtual int d17();
    virtual int d18();
    virtual int d19();
    virtual int d20();
    virtual int d21();
    virtual int d22();
    virtual int d23();
    virtual int d24();
    virtual int d25();
    virtual int d26();
    virtual int d27();
    virtual int d28();
    virtual int d29();
    virtual int d30();
    virtual int d31();
    virtual int d32();
    virtual int d33();
    virtual int d34();
    virtual int d35();
    virtual int d36();
    virtual int vmethod();
};

extern "C" {
void *func_02019de4(unsigned char *p);
void func_0201b1a4(void *dst, UnkStruct_02018b60 *src, int a, int b, unsigned short h);
void func_0201b044(void *dst, void *src);
void func_0201afd4(void *dst, void *src);
void func_0201b350(void *dst, int value);
void func_02016764(void *dst, UnkStruct_02018b60 *src, int vret, unsigned short g, int s1, int s2, int s3, int s4);
void func_02012444(int data, unsigned short g, int c);
void func_02019af0(unsigned char *p);
}

extern volatile unsigned short data_020c80f8;
extern unsigned char data_021fbee8;

extern "C" int func_02018b60(unsigned char *p, UnkStruct_02018b60 *q)
{
    int vret;
    unsigned short h;
    unsigned short r6;
    volatile unsigned short *ptr = &data_020c80f8;

    vret = q->vmethod();
    h = *(unsigned short *) ((char *) func_02019de4(p) + 0x1c);
    func_0201b1a4((char *) q + 0x350, q, 0, 0, h);
    func_0201b044((char *) q + 0x350, (void *) &data_021fbee8);
    func_0201afd4((char *) q + 0x350, (void *) &data_021fbee8);
    func_0201b350((char *) q + 0x3aa, -2);
    r6 = *ptr;
    func_02016764((char *) q + 0x334, q, vret, *ptr, 1, 0x1000, 0, 0);
    if (*(int *) ((char *) q + 0x628) != 0) {
        func_02012444(*(int *) ((char *) q + 0x628), r6, 0);
    }
    *((unsigned char *) p + 0x98) = 0;
    func_02019af0(p);
    return 0;
}
