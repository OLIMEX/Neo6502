if [ ! -d tmp ]; then
	mkdir tmp
fi

#for i in cbmbasic1 cbmbasic2 kbdbasic osi kb9 applesoft microtan; do
for i in osi; do

echo $i
ca65 -I /usr/local/share/cc65/asminc -l tmp/msbasic.lst -D $i msbasic.s -o tmp/$i.o &&
ld65 -vm -m tmp/$i.map -C $i.cfg tmp/$i.o -o tmp/$i.bin -Ln tmp/$i.lbl
done

# For ROM
bintoc -3 -v -b 24 `./getaddress` tmp/osi.bin > tmp/osi.mon
