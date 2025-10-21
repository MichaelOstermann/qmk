# QMK

My keyboard configuration based on https://github.com/qmk/qmk_userspace

## Setup

```sh
# See https://docs.qmk.fm/newbs_getting_started
qmk setup
git clone https://github.com/MichaelOstermann/qmk.git
qmk config user.overlay_dir="$(realpath qmk)"
```

## Compile

```sh
qmk compile -kb splitkb/halcyon/corne/rev2 -km default_hlc -e HLC_ENCODER=1
```

## Resources

- [QMK Firmware](https://docs.qmk.fm)
- [Pascal Getreuer](https://getreuer.info/posts/keyboards/index.html)
