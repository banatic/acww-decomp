/* func_02031c50 @ 0x02031c50, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c30dc;
extern void func_02031eb4(void *arg);
extern void func_02031ea8(void);
extern void __register_global_object(void *a, void (*f)(void), void *b);

struct S02031c50 {
    char pad_00[0x120];
    void *unk_120;
};
extern struct S02031c50 *data_020da1a8;

extern unsigned char data_021c30f8[];
extern unsigned char data_021c3158[];

void *func_02031c50(void)
{
    if ((data_021c30dc & 1) == 0) {
        func_02031eb4((void *) data_021c30f8);
        __register_global_object((void *) data_021c30f8, func_02031ea8, (void *) data_021c3158);
        data_021c30dc |= 1;
    }
    if (data_020da1a8->unk_120 != 0) {
        return data_020da1a8->unk_120;
    } else {
        return (void *) data_021c30f8;
    }
}
