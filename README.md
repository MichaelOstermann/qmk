# QMK

My keyboard configuration based on https://github.com/qmk/qmk_userspace

## Setup

```sh
# See https://docs.qmk.fm/newbs_getting_started
qmk setup
git clone https://github.com/MichaelOstermann/qmk.git
qmk config user.overlay_dir="$(realpath qmk)"
```

## Autocorrect Dictionary

Edit as needed in `features/generate_autocorrect_dictionary.js`

```sh
node features/generate_autocorrect_dictionary.js
```

## Compile/Flash

```sh
qmk compile -kb zsa/voyager -km michaelostermann
qmk flash -kb zsa/voyager -km michaelostermann
```

## Resources

- [QMK Firmware](https://docs.qmk.fm)
- [Oryx Configurator](https://configure.zsa.io/home)
- [Pascal Getreuer](https://getreuer.info/posts/keyboards/index.html)
