zcc +msx -create-app -O3 -DAMALLOC -subtype=msxdos main.c msxclib.c msxalib.c -bn SCLOAD.COM -lm
del SCLOAD.img
move /y SCLOAD.COM bin
cd bin
copy dosformsx.DSK SCLOAD.DSK
START /WAIT DISKMGR.exe -A -F -C SCLOAD.DSK SCLOAD.COM
START /WAIT DISKMGR.exe -A -F -C SCLOAD.DSK HOT.SC8
START /WAIT DISKMGR.exe -A -F -C SCLOAD.DSK fine.sc8
START /WAIT DISKMGR.exe -A -F -C SCLOAD.DSK COLD.SC8
cd ../
