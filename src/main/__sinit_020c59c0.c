/* __sinit_020c59c0 @ 0x020c59c0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020c59c0;

extern unsigned char *func_02060878(void *);
extern void __register_global_object(void *, void *, void *);
extern struct B021cad30 {
    UnkStruct_020c59c0 unk_00;
    UnkStruct_020c59c0 unk_08;
    UnkStruct_020c59c0 unk_10;
    UnkStruct_020c59c0 unk_18;
    UnkStruct_020c59c0 unk_20;
    UnkStruct_020c59c0 unk_28;
    UnkStruct_020c59c0 unk_30;
    UnkStruct_020c59c0 unk_38;
    UnkStruct_020c59c0 unk_40;
    UnkStruct_020c59c0 unk_48;
} data_021cad30;
extern int data_021cad80;
extern void *func_02060844(void *);
extern int data_021cad10;
extern UnkStruct_020c59c0 data_020dd80c;
extern UnkStruct_020c59c0 data_020dd804;
extern UnkStruct_020c59c0 data_020dd7fc;
extern UnkStruct_020c59c0 data_020dd7f4;
extern UnkStruct_020c59c0 data_020dd7e4;
extern UnkStruct_020c59c0 data_020dd7ec;
extern UnkStruct_020c59c0 data_020dd7dc;
extern UnkStruct_020c59c0 data_020dd7d4;
extern UnkStruct_020c59c0 data_020dd7cc;
extern UnkStruct_020c59c0 data_020dd7c4;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c59c0(void)
{
    func_02060878((void *) &data_021cad80);
    __register_global_object((void *) ((void *) &data_021cad80), (((void *) func_02060844)),
                             (void *) ((void *) &data_021cad10));
    data_021cad30.unk_00 = data_020dd80c;
    data_021cad30.unk_08 = data_020dd804;
    data_021cad30.unk_10 = data_020dd7fc;
    data_021cad30.unk_18 = data_020dd7f4;
    data_021cad30.unk_20 = data_020dd7e4;
    data_021cad30.unk_28 = data_020dd7ec;
    data_021cad30.unk_30 = data_020dd7dc;
    data_021cad30.unk_38 = data_020dd7d4;
    data_021cad30.unk_40 = data_020dd7cc;
    data_021cad30.unk_48 = data_020dd7c4;
}

#pragma section INIT end
