IF EXIST "%1\postBuild\proj.hex" (
	ERASE "%1\postBuild\proj.hex"
)

COPY "%1\dist\default\production\ATMEGA328P.X.production.hex" "%1\postBuild\proj.hex"

%1\postBuild\rmvcnfg "%1\postBuild\proj.hex" "%1\postBuild\proj_noconfig.hex" ":0300000040DF07D7"

D:\ProgramData\AVRDUDESS\avrdude -c arduino -p m328p -P COM5 -b 57600 -U flash:w:"%1\postBuild\proj_noconfig.hex":a