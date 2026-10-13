/* func_02072638 @ 0x02072638, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void *data_021d0484;
extern void *data_021d047c;
extern void *data_021d0470;
extern void *data_021d0480;

extern void func_02072594(void *p);
extern void func_020723a0(void *p);
extern void func_020e993c(void *heap, void *p);

void func_02072638(void *p)
{
    void *heap;

    func_02072594((char *) p + 4);
    func_020723a0(p);
    heap = data_021fbe94;
    if (data_021d0484 != 0) {
        func_020e993c(heap, data_021d0484);
        data_021d0484 = 0;
    }
    if (data_021d047c != 0) {
        func_020e993c(heap, data_021d047c);
        data_021d047c = 0;
    }
    if (data_021d0470 != 0) {
        func_020e993c(heap, data_021d0470);
        data_021d0470 = 0;
    }
    if (data_021d0480 != 0) {
        func_020e993c(heap, data_021d0480);
        data_021d0480 = 0;
    }
}
