@echo off


cl /c src/*.c /Ox
link /SUBSYSTEM:WINDOWS *.obj vcruntime.lib user32.lib Advapi32.lib kernel32.lib shell32.lib gdi32.lib /ENTRY:_entry /OUT:shams.exe
del *.obj
strip shams.exe


