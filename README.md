# ccipher
Cesar cipher command line utility

## Cesar Shift Ciphers Simplified

Ever run across an annoying cesear cipher and not know what to do with it?

Ingtmkj znk vurky lxus vray zu sotay gtj lxus sotay zu vray. O grutk yaiikkjkj ot joyiubkxotm znk ykixkz ul hkyzucotm rolk. Tge, kbkt suxk O seykrl hkigsk igvghrk ul hkyzucotm gtosgzout avut rolkrkyy sgzzkx!

That is why I made a commandline program that can work with strings of text that have been shift ciphered.

## Decrypt mystery text
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
Using the --showkeys option also allows for pin-pointing what the decryption key is for the given text.

```bash
$ echo "pants" | ccipher -sa
Key: 1	ozmsr
Key: 2	nylrq
Key: 3	mxkqp
Key: 4	lwjpo
Key: 5	kvion
Key: 6	juhnm
Key: 7	itgml
Key: 8	hsflk
Key: 9	grekj
Key: 10	fqdji
Key: 11	epcih
Key: 12	dobhg
Key: 13	cnagf
Key: 14	bmzfe
Key: 15	alyed
Key: 16	zkxdc
Key: 17	yjwcb
Key: 18	xivba
Key: 19	whuaz
Key: 20	vgtzy
Key: 21	ufsyx
Key: 22	terxw
Key: 23	sdqwv
Key: 24	rcpvu
Key: 25	qbout
```

## Use a specified encryption key
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
```bash
$ echo "pants" | ccipher -e 7 | ccipher -d 7
pants
```


