target := "/tmp/poliorcetics"
config := "keyboards/crkbd/keymaps/poliorcetics/config.h"

# Expects to start with right commented out
both: _prep _right _left
    open {{ target }}
    open /Volumes/RPI-RP2

clean:
    make clean

_left: (_compile "LEFT" "RIGHT")

_right: (_compile "RIGHT" "LEFT")

_prep:
    @mkdir -p {{ target }}

_compile new old: (_side new old)
    qmk compile -kb crkbd/rev1 -e FORCE_LAYOUT=split_3x5_3 -km poliorcetics -e CONVERT_TO=promicro_rp2040 --parallel 0
    mv crkbd_rev1_poliorcetics_promicro_rp2040.uf2 {{ target }}/{{ new }}.uf2

_side new old:
    sd -p '^// (#define MASTER_{{ new }})$' '$1' {{ config }}
    sd '^// (#define MASTER_{{ new }})$' '$1' {{ config }}
    sd -p '^(#define MASTER_{{ old }})$' '// $1' {{ config }}
    sd '^(#define MASTER_{{ old }})$' '// $1' {{ config }}
