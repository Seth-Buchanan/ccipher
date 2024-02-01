# ccipher
## Cesar Shift Ciphers Simplified

Ever run across an annoying cesear cipher and not know what to do with it?

Ingtmkj znk vurky lxus vray zu sotay gtj lxus sotay zu vray. O grutk yaiikkjkj ot joyiubkxotm znk ykixkz ul hkyzucotm rolk. Tge, kbkt suxk O seykrl hkigsk igvghrk ul hkyzucotm gtosgzout avut rolkrkyy sgzzkx!

That is why I made a commandline program that can work with strings of text that have been shift ciphered.

## Decrypt mystery text
With the --allkeys option, the input is decrypted with keys 1-25. The input can be either gathered from stdin or a file.

### File
```bash
$ cat input
grekj
$ ccipher -a input
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
pants
ozmsr
nylrq
mxkqp
lwjpo
kvion
juhnm
itgml
hsflk
```

### Standard In
Using the --showkeys option also allows for pin-pointing what the decryption key is for the given text.

```bash
$ echo "grekj" | ccipher -sa
Key: 1	fqdji
Key: 2	epcih
Key: 3	dobhg
Key: 4	cnagf
Key: 5	bmzfe
Key: 6	alyed
Key: 7	zkxdc
Key: 8	yjwcb
Key: 9	xivba
Key: 10	whuaz
Key: 11	vgtzy
Key: 12	ufsyx
Key: 13	terxw
Key: 14	sdqwv
Key: 15	rcpvu
Key: 16	qbout
Key: 17	pants
Key: 18	ozmsr
Key: 19	nylrq
Key: 20	mxkqp
Key: 21	lwjpo
Key: 22	kvion
Key: 23	juhnm
Key: 24	itgml
Key: 25	hsflk
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


