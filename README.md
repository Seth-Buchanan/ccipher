# ccipher
Cesar cipher command line utility

## Cesar Shift Ciphers Simplified

Ever run across an annoying cesear cipher and not know what to do with it?

Ingtmkj znk vurky lxus vray zu sotay gtj lxus sotay zu vray. O grutk yaiikkjkj ot joyiubkxotm znk ykixkz ul hkyzucotm rolk. Tge, kbkt suxk O seykrl hkigsk igvghrk ul hkyzucotm gtosgzout avut rolkrkyy sgzzkx!

That is why I came up with the idea of making a commandline program that can work with strings of text that have been shift ciphered.

## Usage
With the --allkeys option, the input is decrypted with keys 1-25. The input can be either gathered from stdin or a file.

### File
```bash
$ cat input
pants
$ ccipher -a input
ozmsr
nylrq
mxkqp
lwjpo
kvion
juhnm
itgml
hsflk
grekj
fqdji
epcih
dobhg
cnagf
bmzfe
alyed
zkxdc
yjwcb
xivba
whuaz
vgtzy
ufsyx
terxw
sdqwv
rcpvu
qbout
```

### Standard In
```bash
$ echo "pants" | ccipher -a
ozmsr
nylrq
mxkqp
lwjpo
kvion
juhnm
itgml
hsflk
grekj
fqdji
epcih
dobhg
cnagf
bmzfe
alyed
zkxdc
yjwcb
xivba
whuaz
vgtzy
ufsyx
terxw
sdqwv
rcpvu
qbout
```
The --encrypt and --decrypt options, when given an integer, will shift the input in that direction.

### File
```bash
$ cat input
pants
$ ccipher -e 7 input
whuaz
```
``` bash 
$ cat input
pants
$ ccipher -d 7 input
itgml
```

### Standard In
```bash
$ echo "pants" | ccipher -e 7
whuaz
```
```bash
$ echo "pants" | ccipher -d 7
itgml
```
