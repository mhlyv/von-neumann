# NEUMANN-MODELL

## [(eredeti forráskód itt)](https://github.com/mhlyv/von-neumann)

## UML diagram
![UML](uml.png)

## A főprogram futása (a részletek elkerülésével)
- A főprogram értelmezi a parancssori paramétereket:
	- ```--memory <szám>``` a gép memóriájának mérete (default: 1000)
	- ```--registers <szám>``` a gép regisztereinek száma (default: 10)
	- a futtatni kívánt program forráskódjának fájlneve (kötelező)
- A főprogram készít egy gépet (machine::Machine) a megadott paraméterekkel.
- A főprogram megadja a futtatni kívánt program forráskódjának fájlnevét
a gépnek.
- A gép készít egy *tokenizáló*t (lang::Tokenizer), amelynek beadja
a futtatni kívánt program forráskódjának fájlnevét. A *tokenizáló*
feladata hogy a fájlból úgy olvasson hogy *token*ekre (lang::Token) bontja
a beolvasott sorokat (pl.: insturkció név, instrukció argumentum).
- A gép készít egy *parser*t (lang::Parser), amelynek beadja az előbb
elkészített *tokenizáló*t. A *parser* feladata, hogy a beérkező
*token*ekből értelmezze a forráskód szintaktikáját, és AST-t (abstract
syntax tree) építsen. Itt a parser értelmezi a szekciókat, címkéket és 
instrukciókat.
- A gép meghívja a *parser.write_to()* tagfüggvényt, amely az AST-alapján
létrehozza az *instruckció* (inst::Instruction) objektumokat, és beírja
ezeket a paraméterként megadott memóriába (memory::Memory), és visszaadja
az írt instrukciók számát. Az instrukciók előállítása közben adódó
allokációkat a *parser* eltárolja, és miután végzett az instrukciók
memóriába írásával, újralátogatja az ```"exit"``` instrukciókat, és
mindegyiknek beadja az allokált memóriákat paraméterként, így a program
futásának végén az exit instrukció felszabadítja ezeket, így kerülve a
memóriaszivárgást. A *parser* felelős az instrukciók paramétereinek
értelmezéséért is:
	- ```"<címke>"``` -> az adott címke instrukcióindexe
	- ```"r<szám>"``` -> a processzor <szám>-adik regisztere (*r0* mindig a
	program-counter)
	- ```"<szám>"``` -> számérték (bináris/decimális/hexadecimális)
- Ez után a gép kiadja a parancsot a CPU-nake (cpu::CPU), hogy futtassa
a paraméterként megadott memóriában található programot. Ennek az rendje
hogy a CPU kiolvassa a memóriából a soron következő instrukciót (a 0.
regiszter, azaz *program-counter*) alapján, aztán inkrementálja a
*program-counter*t majd végrehajtja az instrukciót, úgy hogy annak
hozzáférést ad a regiszterekhez (azért az instrukció előtt inkrementál,
mert ha az instrukció ugrást végez, így utólag nem módosítja a *pc*-t),
majd ellenőrzi az instrukció kódját, és ha egy ```"exit"``` instrukciót
hajtott végre akkor nem folytatja a végrehajtást.
- Miután a CPU befejezte a végrehajtást, a gép felszabadítja a memóriában
foglalt instrukciókat.
- Ezek után a főprogram sikeresen kilép, és a destruktorok gondoskodnak
az egyéb allokációk kezeléséről.

## Tesztelés
- A fontos, kisebb elemeket unit tesztek segítégével teszteltem, ezek
forráskódja a az eredeti repository-ban a ```src/test/``` mappában van, a
jportán ha beadom akkor ```test_...``` nevű fájlok. Ezek az eredeti
fordítási rendszeremben egy külön futtatható programfájlba fordulnak,
de csak a *debug* fordítási célban (ennek belépési pontja a
```src/test/test.cpp``` fájlban található). A jportára leadott
forráskódban ez nem lesz, hanem csak a rendes főprogram lesz az egyetlen
futtatható fordítási egység (ennek belépési pontja a ```src/main.cpp```
fájlban található).
- A memóriaszivárgások elkerülését a valgrind
eszközzel és az AddressSanitizer használatával biztosítottam, az eredeti
fordítási rendszeremben a *debug* fordítási célban minden az
```-fsanitize=address``` flag-gel van fordítva.
