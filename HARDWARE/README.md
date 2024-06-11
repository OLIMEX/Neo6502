Contains hardware design files for Olimex Neo6502

Board was designed with free Open Source CAD software - KiCAD, if you have trouble opening the design files use newest KiCAD version.

Folder "3D printed Case" contains STL files for multi material 3D printing of the encolosure.

STL files are designed with Fusion 360

Notable hardware revision changes:

revision B1
======
1. Added diode 1N5819/S4 on FUSE1 pads to enable 5V on HDMI (diode is used to prevent HDMI powering the board). You can try this adjustmest if you have older revision (with nothing placed over FUSE1) and problems with monitor, remember diode has direction and cathode has to be towards the HDMI connector.

revision B
======

1. Changed values P-B-V-40-LF and P-B-V-10-LF;
2. R7 set to 47R/R1206;
3. Added SWITCH1 for the speaker and signals go to the UEXT in case somebody needs them;
4. Added Neo6502 logo;
5. R1 changed NA to 10K;
6. Added attributions names and e-mail at the bottom;
7. C15 and C16 now 18pF;
8. A lot of small adjustmets to reduce soldering problems and yield.

revision A
======

Initial release.