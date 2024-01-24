# ccipher
Cesar cipher command line utility

## Cesar Shift Ciphers Simplified

Ever run across an annoying cesear cipher and not know what to do with it?

Ingtmkj znk vurky lxus vray zu sotay gtj lxus sotay zu vray. O grutk yaiikkjkj ot joyiubkxotm znk ykixkz ul hkyzucotm rolk. Tge, kbkt suxk O seykrl hkigsk igvghrk ul hkyzucotm gtosgzout avut rolkrkyy sgzzkx!

That is why I came up with the idea of making a commandline program that can work with strings of text that have been shift ciphered.

## Usage
By default, in input will be ran through all 26 keys of the shift cipher. The program can either take input through stdin or a specified file.
### File
```bash
$ cat input
pants
$ ccipher input
qbout
rcpvu
sdqwv
terxw
ufsyx
vgtzy
whuaz
xivba
yjwcb
zkxdc
alyed
bmzfe
cnagf
dobhg
epcih
fqdji
grekj
hsflk
itgml
juhnm
kvion
lwjpo
mxkqp
nylrq
ozmsr
```
### stdin
```bash
$ echo "pants" | ccipher
qbout
rcpvu
sdqwv
terxw
ufsyx
vgtzy
whuaz
xivba
yjwcb
zkxdc
alyed
bmzfe
cnagf
dobhg
epcih
fqdji
grekj
hsflk
itgml
juhnm
kvion
lwjpo
mxkqp
nylrq
ozmsr
```

A key can be also be specified that will only print an output shifted by that number.

### File
```bash
$ cat input
pants
$ ccipher --key 12 input
bmzfe
```

### stdin
```bash
$ echo "pants" | ccipher --key 12
bmzfe
```
