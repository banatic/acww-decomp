/* func_02067648 @ 0x02067648, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020ccea0[];
extern "C" int func_020984e8(void);
extern "C" void *func_02099870(int object);
extern "C" void *func_020807dc(void *, void *);
extern "C" void *func_020807c0(void *, void *);
extern "C" signed char func_02081cec(void *, signed char);
extern "C" void *func_02081d20(void *);
extern "C" void func_020787d4(void *, void *, void *);

class UnkStruct_02067648 {
  public:
    virtual void dmy0();
    virtual void dmy1();
    virtual void dmy2();
    virtual void dmy3();
    virtual void dmy4();
    virtual void dmy5();
    virtual void dmy6();
    virtual void dmy7();
    virtual void dmy8();
    virtual void dmy9();
    virtual void dmy10();
    virtual void dmy11();
    virtual void dmy12();
    virtual void dmy13();
    virtual void dmy14();
    virtual void dmy15();
    virtual void dmy16();
    virtual void dmy17();
    virtual void dmy18();
    virtual void dmy19();
    virtual void dmy20();
    virtual void dmy21();
    virtual void dmy22();
    virtual void dmy23();
    virtual void dmy24();
    virtual void dmy25();
    virtual void *target();
};

struct Main {
    char pad_00[0x14a8];
    UnkStruct_02067648 *sub;
};

extern "C" void func_02067648(Main *a, int index)
{
    int forwarded_value;

    if (index == 0) {
        return;
    }
    void *ret1 = a->sub->target();
    (forwarded_value = (int) func_020984e8());
    if (ret1 == 0) {
        return;
    }
    void *p1 = func_02099870((int) forwarded_value);
    void *p2 = func_020807dc(ret1, p1);
    void *p3 = func_020807c0(ret1, p2);
    if (p3 == 0) {
        return;
    }
    signed char c = data_020ccea0[index];
    func_02081cec(p3, c);
    void *r2 = func_02081d20(p3);
    func_020787d4(ret1, p2, r2);
}
