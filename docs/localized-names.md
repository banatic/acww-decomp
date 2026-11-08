# Localized fixed-record names and grammar metadata

```sh
python tools/play.py --form clean --localize es --european path/to/european.nds --latin-keyboard --spanish-grammar --localized-names --build-only
```

`--localized-names` generates a separate `es-grammar-names` resource directory and
`acww-play-es-grammar-names` executable/configuration. It requires the matching Clean runtime:
the extended resources cannot be used by the original interpreter or an older executable.
The generated configuration exports `ACWW_NAMES=1`. Without that setting, record sizes,
virtual text capacities and buffers retain their original behavior. Existing resource paths
and configurations are kept separate. The driver has the same explicit option.

The Korean item tables contain names but no gender or article information. These are not BMG
archives: `/item_info/dma.bin` has 1536 records of 24 bytes, `/ftr_info/dma.bin` has 2048 of
32 bytes, and `/item_info/series.bin` has 128 of 24 bytes. The European localized equivalents
have different layouts. Import only their name and grammar fields, without copying European
prices, model settings or other gameplay data.

Each generated record keeps its complete original Korean prefix byte for byte, with a
64-byte extension: `LTXT`, primary/secondary article indices, gender, one reserved byte, and
56 bytes for a terminated UTF-16 name. All retained record indices keep their numbers.
The reader's configured stride includes that extension only with `ACWW_NAMES=1`. Other
fields continue to be read from their original offsets. Series names have no invented
article or gender metadata. The generator rejects mismatched counts, partial records,
control bytes and names exceeding the bounded extension.

NameText's original 22-byte inline buffer is too short for many Western names. PlayerIdText
and TalkReceiverName also carry special-character names through 14-byte buffers. Their
localized virtual buffer/capacity slots use per-object 64-byte host buffers, leaving the
actual object layouts and persistent player/town name fields unchanged. Both destructor
paths of each class release its buffer. The name plate is bounded by the active capacity.
This accommodates names of up to 31 UTF-16 characters; the generated record format permits
at most 27. The persistent six-character player/town name limits are unchanged.

The existing opt-in Spanish grammar handlers can now read actual item/furniture genders and
article indices. Live Clean checks show the definite feminine article before the shovel's
name and the feminine purchase question. The 15-character paper name, including U+00ED,
appears complete in the pockets popup. The speaker label also shows the full eight-character
Nook name without truncation. These checks use the prepared town fixture documented in
`localized-playtests.md`; no private assets or screenshots are committed.

Five synthetic tests cover retained prefixes, long names, accents, absent series metadata,
invalid records, default-disabled behavior, bounded extension reads, independent owner
buffers and destructor/reuse behavior. The actual C helper is compiled and executed in CI.
This change does not by itself map regional dialogue indices or translate the remaining
incompatible archives, including the separately identified fish capture archive.

The supported private dumps were also checked for all five language folders: every name
record converts, keeps its original prefix and fits the bounded extension. With the feature
disabled, the original 13760-frame new-game recording matches Reference and its expected
SHA-1, `16893c6096451529d7390ad866773dffe727991c`.
