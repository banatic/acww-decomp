/* func_02051880 @ 0x02051880, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02050c58(unsigned short *out, const unsigned char *in);

class UnkStruct_02051880 {
  public:
    virtual void f0();
    virtual void f1();
    virtual unsigned int f8();
    virtual void *fC();
};

extern "C" int func_02051880(UnkStruct_02051880 *a, UnkStruct_02051880 *b)
{
    unsigned char *inPtr = (unsigned char *) b->fC();
    unsigned int inputLen = b->f8();
    unsigned int total = 0;
    unsigned short *outPtr = (unsigned short *) a->fC();
    unsigned int outputLen = a->f8();
    unsigned int outIndex = 0;
    int result = 1;
    unsigned short ch;

    while (total < inputLen && outIndex < outputLen) {
        int adv = func_02050c58(&ch, inPtr);
        *outPtr = ch;
        outPtr++;
        outIndex++;
        inPtr += adv;
        total += adv;
    }

    if (outIndex >= outputLen && *inPtr != 0) {
        result = 0;
    }

    while (outIndex < outputLen) {
        *outPtr = 0;
        outIndex++;
        outPtr++;
    }

    return result;
}
