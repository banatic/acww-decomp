"""Conservative word counts for Native calls into the ROM.

Unknown signatures retain the legacy bridge extent. A parameter count alone
cannot describe structures, member pointers, 64-bit arguments or varargs.
"""
from __future__ import annotations

import hashlib
import re

import protos

COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
QUALIFIERS = {"const", "volatile", "register", "static", "inline", "extern", "__arm", "__thumb"}
WORD_TYPES = {
    "char", "signed char", "unsigned char", "short", "short int", "signed short",
    "signed short int", "unsigned short", "unsigned short int", "int", "signed",
    "signed int", "unsigned", "unsigned int", "long", "long int", "signed long",
    "signed long int", "unsigned long", "unsigned long int", "u8", "s8", "u16", "s16",
    "u32", "s32", "BOOL", "bool", "float", "f32", "fx16", "fx32", "size_t",
}
WIDE_RESULTS = {"long long", "long long int", "unsigned long long", "unsigned long long int",
                "signed long long", "signed long long int", "u64", "s64", "double", "f64"}


def scalar_type(declaration: str, named: bool) -> str | None:
    """A proven one-word type, or a scalar result type; never infer typedefs."""
    # A default expression can contain '*' or '&' without declaring a pointer.
    # Reject unsupported declarators before inspecting pointer/array syntax.
    if (re.search(r"::\s*\*", declaration) or "..." in declaration
            or any(token in declaration for token in ("<", "=", "{", "}", "?"))):
        return None
    if "*" in declaration or "&" in declaration or "[" in declaration:
        return "pointer"
    words = [w for w in declaration.split() if w not in QUALIFIERS]
    kind = " ".join(words)
    if kind in WORD_TYPES | WIDE_RESULTS | {"void"}:
        return kind
    if named and words and re.fullmatch(r"\w+", words[-1]):
        return " ".join(words[:-1])
    return kind


def word_arguments(text: str, name: str) -> int | None:
    """Count words for explicit scalar/pointer free-function definitions.

    Assembly definitions and unknown result types may use an undocumented ABI.
    Structures returned by value can add a hidden argument, so they stay unknown.
    """
    text = COMMENT.sub(" ", text).replace('extern "C"', " ")
    pattern = (r"(?:^|[;}])\s*((?:[\w<>]+[\s\*&]+)+?)((?:\w+::)?)" + re.escape(name)
               + r"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(?:const\s*)?\{")
    matches = list(re.finditer(pattern, text, re.M))
    if len(matches) != 1:
        return None
    match = matches[0]
    if "asm" in match[1].split() or match[2]:
        return None
    # A qualified definition alone cannot distinguish static from instance
    # members. An inline class definition can also hide an implicit `this`.
    if any(start <= match.start(1) < end for start, end in protos.class_bodies(text)):
        return None
    if scalar_type(match[1], False) not in WORD_TYPES | WIDE_RESULTS | {"void", "pointer"}:
        return None
    params = match[3].strip()
    if params in ("", "void"):
        return 0
    parts, depth, start = [], 0, 0
    for index, ch in enumerate(params):
        depth += ch == "("
        depth -= ch == ")"
        if ch == "," and depth == 0:
            parts.append(params[start:index])
            start = index + 1
    parts.append(params[start:])
    if any(scalar_type(part, True) not in WORD_TYPES | {"pointer"} for part in parts):
        return None
    return len(parts)


# Assembly library functions whose ROM code never uses the stack pointer and never leaves the
# function (no call, no branch outside it): whatever their declaration says, they read no
# argument from the stack, so a Native call into one writes no stack words (the ROM's callers
# do not either, and the words would cover residue later code reads: scene villager-habit2).
# (module, address) -> (name, size, SHA-256 of the ROM code); test_native_abi.py derives the
# list from the ROM with capstone.
STACKLESS_ASM: dict[tuple[str, int], tuple[str, int, str]] = {
    ('autoload_2', 0x02112150): ('GXi_NopClearFifo128_', 0x94,
        'b829db3b5e40e87e4edeacb39c8554be4fe06384eeab2ad0264f0bc532378f82'),
    ('autoload_2', 0x021137d8): ('GX_SendFifo48B', 0x24,
        'ecb39de0efdc5098c0ec15af8680ae4059d24aa68073f502354c1a80dab27a84'),
    ('autoload_2', 0x02113974): ('OS_ReleaseLockID', 0x30,
        '274fcbc8387fdbfa2b6fe7cf75cd25eeb0e1f19ab24402739d7c7535e8368198'),
    ('autoload_2', 0x021153b8): ('OS_InitContext', 0x64,
        'caf5bef92278085533e04e3e70a14868d3b80249195569a280df0da225e14e43'),
    ('autoload_2', 0x02115a74): ('DC_InvalidateAll', 0xc,
        '87350088fc719c962c49919a6028cbdc10b61366d416c37fcabfd86f05a3341f'),
    ('autoload_2', 0x02115a80): ('DC_StoreAll', 0x2c,
        '982e7f61332a95eacb9182a4e7b554a7d652a4fa704ed02157320885035f3f22'),
    ('autoload_2', 0x02115aac): ('DC_FlushAll', 0x34,
        'b630a9f2607ee24a57aee9567fc0bd28e7639a47c11c81fcbd50c73829e309f9'),
    ('autoload_2', 0x02115ae0): ('DC_InvalidateRange', 0x1c,
        '48901f21488a7733a2d5bd5ebf22720782c22fc6b02adb500e923c60c4bd8a20'),
    ('autoload_2', 0x02115afc): ('DC_StoreRange', 0x1c,
        '73c490c748591560c32073177db61f3e23b90fb4814786885fd11b1277df2f0b'),
    ('autoload_2', 0x02115b18): ('DC_FlushRange', 0x24,
        'afafd34da03d3444cf60b68f45b2e6eab2e36b9a31a7dde8bf3d12187467e843'),
    ('autoload_2', 0x02115b3c): ('DC_WaitWriteBufferEmpty', 0xc,
        'c27ce0bc897baa92f297f607f9677de717c8702b912841eeb8cfc4a5d7d4a16c'),
    ('autoload_2', 0x02115b48): ('IC_InvalidateAll', 0xc,
        '1b9b31e8b186194b339e53e686f9c6caf9dffc7cfaed0250cb22939a495ff93e'),
    ('autoload_2', 0x02115b54): ('IC_InvalidateRange', 0x1c,
        'ffca60a25c2f00ded333c78f7bd5a9d3af59108f936fdb2c75b675bc8eadf992'),
    ('autoload_2', 0x021160b4): ('OS_EnableDTCM', 0x10,
        'f336efa2009ee478e1032c27ddd39641677495cc3d5e8545ebdbe15f73813008'),
    ('autoload_2', 0x021160d8): ('OS_EnableProtectionUnit', 0x10,
        'a54f1f3201a56509e6a0727e44f68ca4f479e222921ff268e2372feb98b6f8d8'),
    ('autoload_2', 0x021160e8): ('OS_DisableProtectionUnit', 0x10,
        'e2198bc0e9e6362a947b8f7f58b87509a209bd79c12981f1c91eb3fc6b2838ec'),
    ('autoload_2', 0x021160f8): ('OS_SetProtectionRegion1', 0x8,
        '6e9918c3ae85c4beba206bb22bdbbbc76808da64f56d439644a4df5843bb707b'),
    ('autoload_2', 0x02116100): ('OS_SetProtectionRegion2', 0x8,
        '92431ce8a41e4a29855e6b5e9757ee5c9798e357db757638f24b6a14f5f09791'),
    ('autoload_2', 0x02116c10): ('OsCountZeroBits', 0x8,
        '060682c80d3a37098de575f51eabcbe853bedcd07c00051f839c558df4b37d67'),
    ('autoload_2', 0x021173e4): ('MIi_CpuClear16', 0x18,
        'd2d14fd6d81c53ad277449040bee12a49b3865b82e204ddf1788ba2d8b785bc7'),
    ('autoload_2', 0x021173fc): ('MIi_CpuCopy16', 0x1c,
        'b13a643d9bdfb04665304652c4e2d7e061e91b77f7832e6f3e9f50e62e37bda8'),
    ('autoload_2', 0x02117418): ('MIi_CpuClear32', 0x14,
        '3cfd563af82d5813c8180f4b189a1e34d77a9c562334d174657e0d116c7d988e'),
    ('autoload_2', 0x0211742c): ('MIi_CpuCopy32', 0x18,
        '11b33393cb66eec6392d208c96cdea91fc66ad9d1ea9b3ad8d32a727d66489b8'),
    ('autoload_2', 0x02117444): ('MIi_CpuSend32', 0x18,
        'ed10452abe309f9ccabb5a302958ab0346751b510769f47abc86894b97589a5f'),
    ('autoload_2', 0x0211745c): ('MIi_CpuClearFast', 0x4c,
        '78d9fa528b10650a11d403d7be899508367353e15fa6b5fb691566cf9b9e2f71'),
    ('autoload_2', 0x021174a8): ('MIi_CpuCopyFast', 0x38,
        '03dedb056d93e4d67f696cbce2aa102d149753258cf8d227ad819003781b5a3d'),
    ('autoload_2', 0x021174e0): ('MI_Copy32B', 0x1c,
        '82bd196db53d45573ffc89bdc28202ef5f2634bfeaa20817ab94a38238fa1311'),
    ('autoload_2', 0x021174fc): ('MI_Copy36B', 0x1c,
        '589bf04eb1792b8434ef1e17b8b3895652d792c16c85de3730dd17223abbfa3a'),
    ('autoload_2', 0x02117518): ('MI_Copy48B', 0x24,
        'd9a84fcf48143a2bbf70e084ee6b1a76fbae459cced44c3166f72b5ab5aa6ca9'),
    ('autoload_2', 0x0211753c): ('MI_Copy64B', 0x2c,
        'cb45d51c411b14ca622d146ba77e1b16c6076b1e5710228cbb14fb41a3268a27'),
    ('autoload_2', 0x02117568): ('MI_CpuFill8', 0x94,
        'c88796aaf6fcd87ae6cbd3d7000128d6e4035339a3b826a851053a0ba02d07a8'),
    ('autoload_2', 0x021175fc): ('MI_CpuCopy8', 0x130,
        '9c23b2fac113088842e50833d03da93628c9e0a12066d5136299ea38f1df8c0b'),
    ('autoload_2', 0x0211772c): ('MI_Zero36B', 0xe,
        '9346be17ffed8b6569f19dbca263f47f5c29991a8431170b97ece7d6bc64ebc9'),
    ('autoload_2', 0x0211773c): ('MI_SwapWord', 0x8,
        '97cc6ada39388bbf4899441b1363060543fa78d5477c410985b5f214641a9f25'),
    ('autoload_2', 0x02117744): ('MI_UncompressLZ8', 0x94,
        'b1397528f6c6d704cc8916ae6e05cea3693d240091502ead3b90bf639ca78011'),
    ('autoload_2', 0x02117864): ('MI_ReadUncompLZ8', 0x100,
        'bdd81ac05654879d59966df84051d33a51481269004e45b9e83cf2eb32cab4c8'),
    ('autoload_2', 0x0211e184): ('RtcWaitBusy', 0x18,
        '3d3614f3f9707a2bb80bf0b073ddbfb3961ba40edb2d35f973b5e9585f026402'),
    ('autoload_2', 0x02134508): ('_d2f', 0x104,
        '46d1b63c88842e40fffdc01550cd8902742a3ced15bb4c22b9cc8cf0ebf7d459'),
    ('autoload_2', 0x0213460c): ('func_0213460c', 0x58,
        'ec215384d1cf23dc4be407c66ab6909a430d5107b89695fbe7a390c9c65ac078'),
    ('autoload_2', 0x02134664): ('_ll_ufrom_d', 0x8c,
        '69a48b26acc1871c63b88f7920dc071f4111e0b99aae88821b76a956890bae8a'),
    ('autoload_2', 0x021346f0): ('_dfltu', 0x3c,
        '3859ba8fff3004ff81ea2ce721d63ef25ac866b11195e2526af9971b6fa4e472'),
    ('autoload_2', 0x0213472c): ('_dflt', 0x40,
        '7478e16a269a5835b5258a7df8529b2bf9021a7106421a7ae9623a01b9ac4a4a'),
    ('autoload_2', 0x0213476c): ('_dmul', 0x364,
        '16a30a586ebe9ac165d52d79b8d6ece3be666b610328fe3fc4a778744e676c4e'),
    ('autoload_2', 0x0213524c): ('func_0213524c', 0x48,
        'c433d993c21aaea93f792ea923003cd763a2f5742a32639f22dcc5ec14562b63'),
    ('autoload_2', 0x02135294): ('func_02135294', 0x40,
        'd6ee933f37ecc0cbf49ef1323117f0956d314c837fd8221b377cfaa40bb51339'),
    ('autoload_2', 0x021352d4): ('func_021352d4', 0x3c,
        'fb2746ad9a50341af01972614ecbf06850184b1a8f319e6d17389a43b135726d'),
    ('autoload_2', 0x02135310): ('func_02135310', 0x3c,
        '4fa2851940a6aeb736e3b0670119ad8f31c1c82356999a577f84cc306f300f03'),
    ('autoload_2', 0x0213534c): ('func_0213534c', 0x38,
        '87eb77e2e555051dfcaef8253ed0c331038509e041fd55b999995c9fb51f6a52'),
    ('autoload_2', 0x02135384): ('_fls', 0x3c,
        '01839f2aef81d2f616c1a4e8eee4a11b4367a3d5704c397f376120b6b4334c6a'),
    ('autoload_2', 0x021353c0): ('func_021353c0', 0x3c,
        '31a4ec321ba30c4eb13645dd68b2b3ed84b9a234a80aecd5ec227341dd508d23'),
    ('autoload_2', 0x021353fc): ('func_021353fc', 0x44,
        '285310e5a9d4f41fd090e18d865d28569ec73e325c3bb641dc24104623be4980'),
    ('autoload_2', 0x02135440): ('_fgr', 0x3c,
        'a5d345165fb663b703a479bf15a153874ac7978d4418af175d3abf88b253a5ba'),
    ('autoload_2', 0x0213547c): ('func_0213547c', 0x3c,
        '3be1a97c31fae0cd754d9192c8549f820e2559105a6e58e31de654d5ab57a7f9'),
    ('autoload_2', 0x021354b8): ('func_021354b8', 0x3c,
        '518c8a1e7c1a2bac163131a5a24fa375ceea274c9769f4d99dc7d03710c35262'),
    ('autoload_2', 0x021354f4): ('func_021354f4', 0x24,
        '83c9844ce6aff98f1b0021a3f97ff0e98f56c784445819435506f7cfaf3f0143'),
    ('autoload_2', 0x02135518): ('func_02135518', 0x24,
        '9216ec6b4e0f80bbf8ac2316afcce513421a19749572c55f94cd37fb1b3a79cb'),
    ('autoload_2', 0x0213553c): ('func_0213553c', 0x90,
        '7f4d36fb7ad5b9ff20ae607182fad5000be98810e0b7e1b24fc1b386a1c37dee'),
    ('autoload_2', 0x021355cc): ('func_021355cc', 0x90,
        '7f4d36fb7ad5b9ff20ae607182fad5000be98810e0b7e1b24fc1b386a1c37dee'),
    ('autoload_2', 0x0213565c): ('_dneq', 0x88,
        '450f6204375f0b8c48ab2c885030daa465996822175928f7e3d02e5422e87507'),
    ('autoload_2', 0x021356e4): ('_deq', 0x88,
        '19693ec333108dcb6774c943a09df50626fe73fe8ec91ff6e389c515bd1e5423'),
    ('autoload_2', 0x021357f0): ('_dls', 0x88,
        '2959ddbef01171818dbd0eded95b3bce8b22d87934dc3ed8371b650ffa466e93'),
    ('autoload_2', 0x02135878): ('_dleq', 0x88,
        '0302d37099e671c58a9109d3364e2536b01af6ccc834c038b688206d06f2243e'),
    ('autoload_2', 0x02135900): ('func_02135900', 0x94,
        '3fe273274b40df40bfd38eff07ea5b4da50f5ecf5899ce7c73f62e20ca925fe5'),
    ('autoload_2', 0x02135998): ('_dgr', 0x88,
        '6efcf27d318a8f8541713fb287cd4acb38f9f36ae7334d296bb813e506c358bd'),
    ('autoload_2', 0x02135a20): ('func_02135a20', 0x88,
        'fa005fa95f9d66a0f14a67a99b632d60f3ee54618ac24826da83eac9b684f8ed'),
    ('autoload_2', 0x02135aa8): ('func_02135aa8', 0x94,
        '8c5a1c2d87c296aa337305e8d329f6797b5d7211edf56a2b70ffdc6171d619e6'),
    ('autoload_2', 0x02135b40): ('func_02135b40', 0x50,
        'fcfdb68ad0a549cf64e1c99e4261c6cc0066c24bfa233cbdecf74fcf8dcd3521'),
    ('autoload_2', 0x02135b90): ('func_02135b90', 0x50,
        '5135123b26c5a65b90c92ad61e1d6524158ed5f6774a49cb63802c7fea0a5ce3'),
    ('autoload_2', 0x02135fa4): ('_f2d', 0x84,
        '29e8c250fe28c58be66a491d6465ae3c794af8831906ec999a9e1ed1450d766c'),
    ('autoload_2', 0x02136028): ('_ffix', 0x34,
        'd5fd0208b26ed20e8eb752c2d96599d06f504fdb31f79713269d19abe2fb9e91'),
    ('autoload_2', 0x0213605c): ('func_0213605c', 0x48,
        '770a6347a450031c316f34fcb22fcf452a2bd1a0f2fcd1abb3b7b70f146dd8ba'),
    ('autoload_2', 0x021360a4): ('_fflt', 0x48,
        '23ede7780499aa4d14fc532deb5e0ea7b35ee3b155dc70327368c88037330563'),
    ('autoload_2', 0x021360ec): ('_fmul', 0x1e0,
        '21410393c8ab1edc30019dd39efd54e8e35b8ca31c39c92fbd114e2211af8bed'),
    ('autoload_2', 0x02136758): ('_ll_mul', 0x20,
        '661b48b2adf3a6af3987ca653b5aaa2172d0d5137c91c6658cf18189b776a714'),
    ('autoload_2', 0x02136778): ('func_02136778', 0x30,
        'cd85e331b68cde1500bc5993fcc798229d39975d58570f65d52a9b43e8165d67'),
    ('autoload_2', 0x021367a8): ('_s32_div_f', 0x20c,
        'e8183a62ffe6a54210cd7d025b01431ff792025c1b45a0e8537abd8cec16ccfb'),
    ('autoload_2', 0x021369b4): ('_u32_div_f', 0x1e4,
        '3b0403581ea03e86bdfc0cde00ea2ca13f522291aec399b93ecdf2fef57944eb'),
    ('autoload_2', 0x02136b98): ('func_02136b98', 0x30,
        '0dd1508575a7a80559b978f91b7483a646a26e2d5a036c870c865a8f77816d1c'),
    ('autoload_2', 0x0213734c): ('func_0213734c', 0x10,
        '570173cea185f5748ea246c8db528d2cc87d86099124b7d8a09d9356c5942518'),
    ('itcm', 0x01ffa2ec): ('OS_DisableInterrupts', 0x14,
        'a8cdb747f9936730571b220bb9570615892665b120713ffc59b1cb2d7dee76ff'),
    ('itcm', 0x01ffa300): ('OS_DisableInterrupts_IrqAndFiq', 0x14,
        'a28a74d99483b6248b1f1a2ab98c2761d430292a639b4809dbd943f8933db59b'),
    ('itcm', 0x01ffa314): ('OS_EnableInterrupts', 0x14,
        '7c5724bfdbcfb52c6253bb57b74c12bf1e98e4526cb4ecdb0fade4c9e10dbfa2'),
    ('itcm', 0x01ffa3c0): ('OS_Halt', 0xc,
        '41cf2639ff0928e5c67f842db7e28825020db50d66cef85d75c3943ce8b4b6ac'),
    ('itcm', 0x01ffa3d4): ('OS_RestoreInterrupts', 0x18,
        '46b5111b6fad094dfff177dca974d33b477cb72772ecfe95b74b1c7f656bc4fd'),
    ('itcm', 0x01ffa3ec): ('OS_RestoreInterrupts_IrqAndFiq', 0x18,
        '1af689f0cb6ad8ac8c2e194779405f35aa692853028b83859dd018f50008f229'),
    ('itcm', 0x01ffa494): ('OS_SpinWait', 0xc,
        'f7e146ee9e88c39b1758c3dd337d6e4d5cf4bb336b965a5f72911e6bd4a17587'),
    ('itcm', 0x01ffb448): ('MTX_Identity33_', 0x24,
        '2f436dbece5b115fccfb27246b8ddaacbd01e820707ac3d57181122f12b64f37'),
    ('itcm', 0x01ffb46c): ('MTX_Copy33To43_', 0x2c,
        '2a53a6e4a236d6fa21adf830141c9b378c9075f3ec04d289d127523c4bb68f25'),
    ('itcm', 0x01ffb498): ('MTX_RotX33_', 0x1c,
        '7f43f0d2699726a8f0cc12620e52ebd83f8aa6ee219a1097d26f19e8b3a67510'),
    ('itcm', 0x01ffb4b4): ('MTX_RotY33_', 0x1c,
        'f2909671f3fa927b0e9b6a32f865d7d34ec31619ceb15a2e3ce3a2f90e54a942'),
    ('itcm', 0x01ffb4d0): ('MTX_RotZ33_', 0x18,
        'a6d1dfbde73c8c629d95075631c88a75bd015ed65668060e607581c807711fed'),
    ('itcm', 0x01ffb7cc): ('MTX_Identity43_', 0x28,
        '5aa80ef15096ef9bcf995983c2a274f91eaa7f9d8c9b2a733d0b29e1fb61d460'),
    ('itcm', 0x01ffb828): ('MTX_Scale43_', 0x16,
        '532ee9ac73571ceaed1df74b323461bd53c0ebbd8cbd727105436e0b97488c72'),
    ('itcm', 0x01ffb840): ('MTX_RotX43_', 0x1e,
        '714d2cd17ba947201e28b76261c3db637fcdccc56d609e5fbb637c0677f3fab3'),
    ('itcm', 0x01ffb860): ('MTX_RotY43_', 0x1a,
        '1bb0b5b0d900b6f7d79c1b969c29ec6eed6cc12a4bf9b4b8419b66da56561296'),
    ('itcm', 0x01ffb87c): ('MTX_RotZ43_', 0x1a,
        '81b986ed5bc3e582caea8a243336359a1bdc92c638a486c5703267c3ddec84ea'),
    ('itcm', 0x01ffbf40): ('MTX_Identity44_', 0x2c,
        '48842e5c2a9162e6ae1312b49d49ca81fb9660851fee699519e102f3831093dc'),
    ('itcm', 0x01ffbf6c): ('MTX_Copy44To43_', 0x34,
        '3aee4c529747747514bd3ed75e62d2341524c3a8e4c1805a0533e78a948e6f7e'),
    ('itcm', 0x01ffd770): ('OSi_CpuClear32', 0x14,
        '3cfd563af82d5813c8180f4b189a1e34d77a9c562334d174657e0d116c7d988e'),
    ('main', 0x0200007a): ('IntrWait', 0x4,
        '485d13214d02ed051e795d47865ceea1fe4d5b310e8efae318bee4a62cb63b47'),
    ('main', 0x020000e2): ('LZ77UnCompReadNormalWrite8bit', 0x4,
        'ec6d14bbc6d782be7f74aa1a98008404ecc1d3324187a7989458b17708869e80'),
    ('main', 0x02000156): ('Halt', 0x4,
        '8e93a1720c694e06005b83e2dbaf36a800649ab8948fc4e15efa39309f4c5ce6'),
    ('main', 0x020001a0): ('LZ77UnCompReadByCallbackWrite16bit', 0x4,
        '4f32a5a0727704ed8cc1e46af9875d484bb379b73cdd4ae15086deeb7426b8a0'),
    ('main', 0x020001fe): ('CpuSet', 0x4,
        '07967ebdc3979cd4fd4de37fd22b3e6de8965b00dae4ac5585577c9709839652'),
    ('main', 0x02000270): ('Mod', 0x6,
        '60fbe450e50aaefd910a0b8dc4b96ebf7f2e159fcf32ef9592c6641842f866e6'),
    ('main', 0x020002c6): ('VBlankIntrWait', 0x6,
        'bf9fc420439437739d9c6b74b51fbe54a172af5a3d24fd499ba4acd0bc9c4050'),
    ('main', 0x02000338): ('CpuFastSet', 0x4,
        'dedc152a89df8aadc9dc9526881c29e92f681504cf9bf438bbac1c6362fd9b42'),
    ('main', 0x020003a8): ('HuffUnCompReadByCallback', 0x4,
        '6f60ae217f4bca5053cbb060d3927260ca950e3fda49650c28311d325ab5858e'),
    ('main', 0x02000418): ('RLUnCompReadNormalWrite8bit', 0x4,
        'f1048b99d6e37687865f22863a77e61648b8054a57ca380b03dad2594796b86d'),
    ('main', 0x02000474): ('IsDebugger', 0x4,
        '9f004ab9239029bc7e051e24763751da64c47109e542f1d19f241ac89ceccb39'),
    ('main', 0x02000544): ('WaitByLoop', 0x4,
        '498a35dfd2a6c72167d58697263323cd3392f37ed1ef8eddc11ed0852fb1720b'),
    ('main', 0x020005c2): ('GetCRC16', 0x4,
        '7db5376a9255b6f3b335a2a0553165e6f8fb14695e62f9b3797fb876191ee72a'),
    ('main', 0x0200062e): ('RLUnCompReadByCallbackWrite16bit', 0x4,
        '92180fdd5a99d438bbf8c27c41c529abc571a5cd47d4e6d10311a84b4c44859c'),
    ('main', 0x02000698): ('Div', 0x4,
        '8911c2f5cca009dc112aed3996c2516b5949669109b1c79881bfb940b0f14e7c'),
    ('main', 0x02000712): ('BitUnPack', 0x4,
        '6e20b0803117ba9fffba8ee7e11d8d62b4ddf8fe18230eb3f90251c58614806e'),
    ('main', 0x02000788): ('SoftReset', 0x4,
        '0047f9d2959e3a3cd24f18be3adbfeddd3b2259e27e52eb8fcffac6211c15407'),
    ('main', 0x02000920): ('INITi_CpuClear32', 0x14,
        '3cfd563af82d5813c8180f4b189a1e34d77a9c562334d174657e0d116c7d988e'),
    ('main', 0x02000934): ('MIi_UncompressBackward', 0xac,
        'c3979e93bb0e390fbef9cf64dd91479895dee1945ad61c964af19e34fefb976f'),
    ('ov065', 0x02270278): ('WcmCountBits', 0x24,
        'e730c29fb0bcb449fa667357b9a3fd23298cc89139f2e82ced649dbfed3a2098'),
    ('ov065', 0x0227029c): ('WcmCountLeadingZero', 0x8,
        '060682c80d3a37098de575f51eabcbe853bedcd07c00051f839c558df4b37d67'),
}


def stackless_asm(module: str, address: int, code: bytes) -> bool:
    """Whether (module, address) is a STACKLESS_ASM function whose ROM code is still `code`."""
    spec = STACKLESS_ASM.get((module, address))
    if spec is None:
        return False
    if len(code) != spec[1] or hashlib.sha256(code).hexdigest() != spec[2]:
        raise ValueError(f"Stackless library code changed; repeat the audit: {module}:{address:08x}")
    return True
