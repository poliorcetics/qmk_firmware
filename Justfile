target := "/tmp/poliorcetics"
config := "keyboards/crkbd/keymaps/poliorcetics/config.h"

# Expects to start with right commented out
both: prep right left
    open {{ target }}
    open /Volumes/RPI-RP2

clean:
    make clean

[private]
left: (compile "LEFT" "RIGHT")

[private]
right: (compile "RIGHT" "LEFT")

[private]
prep:
    @mkdir -p {{ target }}

[private]
compile new old: (side new old)
    qmk compile -kb crkbd/rev1 -e FORCE_LAYOUT=split_3x5_3 -km poliorcetics -e CONVERT_TO=promicro_rp2040 --parallel 0
    mv crkbd_rev1_poliorcetics_split_3x5_3_promicro_rp2040.uf2 {{ target }}/{{ new }}.uf2

[private]
side new old:
    sd '^// (#define MASTER_{{ new }})$' '$1' {{ config }}
    sd '^(#define MASTER_{{ old }})$' '// $1' {{ config }}
