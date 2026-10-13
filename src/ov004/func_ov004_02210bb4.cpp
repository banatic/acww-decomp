/* func_ov004_02210bb4 @ 0x02210bb4, 0x13c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" char data_ov004_02259698[];
extern "C" void *func_ov004_0223ce84(void);
extern "C" int func_ov004_0223ce18(void *, char *);
extern "C" void *func_0209d238(void *, void *);
extern "C" void func_ov004_0220f52c(char *);
extern "C" int func_0203efbc(char *);
extern "C" unsigned short func_ov004_0220e808(char *, int, int);
extern "C" void func_0203efb0(char *, int);
extern "C" int func_ov004_0220e1a0(void *, void *, int, int);
extern "C" int func_ov004_0220e080(void *, void *, int, int);
extern "C" int func_ov004_0220e068(void *);
extern "C" int func_ov004_0220e050(void *);
extern "C" int func_02055f2c(void *, int, int);
extern "C" int func_ov004_0220f484(char *);
// Reconstructed vtable slots at byte offsets 0x7C and 0x8C.
class Actor {
  public:
    virtual int slot0();
    virtual int slot1();
    virtual int slot2();
    virtual int slot3();
    virtual int slot4();
    virtual int slot5();
    virtual int slot6();
    virtual int slot7();
    virtual int slot8();
    virtual int slot9();
    virtual int slot10();
    virtual int slot11();
    virtual int slot12();
    virtual int slot13();
    virtual int slot14();
    virtual int slot15();
    virtual int slot16();
    virtual int slot17();
    virtual int slot18();
    virtual int slot19();
    virtual int slot20();
    virtual int slot21();
    virtual int slot22();
    virtual int slot23();
    virtual int slot24();
    virtual int slot25();
    virtual int slot26();
    virtual int slot27();
    virtual int slot28();
    virtual int slot29();
    virtual int slot30();
    virtual int slot31();
    virtual int slot32();
    virtual int slot33();
    virtual int slot34();
    virtual int slot35();
};
typedef struct {
    unsigned int low : 26, mode : 2, high : 4;
} Flags;
// The ROM reserves twelve bytes for this local flag view; only its first word is read.
static inline unsigned int mode(unsigned int flags)
{
    union {
        unsigned int word;
        Flags bits;
        unsigned int storage[3];
    } frame;
    frame.word = flags;
    return frame.bits.mode;
}
extern "C" int func_ov004_02210bb4(char *self)
{
    void *resource;
    int first;
    *(int *) (self + 0x76c) = mode(*(unsigned int *) (self + 8));
    func_ov004_0223ce18(func_ov004_0223ce84(), self);
    resource = func_0209d238(data_ov004_02259698, self + 0x132);
    func_ov004_0220f52c(self);
    if (!func_0203efbc(self)) {
        func_0203efb0(self, func_ov004_0220e808(self, 0, 0));
    }
    if (*(int *) (self + 0x76c) == 0) {
        func_ov004_0220e1a0(self + 0x6cc, resource, *(int *) (self + 0x284), ((Actor *) self)->slot35());
        first = func_ov004_0220e068(self + 0x6cc);
        func_02055f2c(self + 0x538, first, func_ov004_0220e050(self + 0x6cc));
        self[0x77e] = 1;
        func_ov004_0220f484(self);
        if (((Actor *) self)->slot31()) {
            self[0x77e] = 0;
            return 1;
        }
        return 0;
    } else {
        if (func_ov004_0220e080(self + 0x6cc, resource, *(int *) (self + 0x284), ((Actor *) self)->slot35())) {
            first = func_ov004_0220e068(self + 0x6cc);
            func_02055f2c(self + 0x538, first, func_ov004_0220e050(self + 0x6cc));
            self[0x77e] = 1;
            func_ov004_0220f484(self);
            if (((Actor *) self)->slot31()) {
                self[0x77e] = 0;
                return 1;
            }
            return 0;
        }
        return -1;
    }
}
