IF EXIST "C:\Users\160047412\Desktop\proj.hex" (
	ERASE "C:\Users\160047412\Desktop\proj.hex"
)

COPY "dist\default\production\ATMEGA328P.X.production.hex" "C:\Users\160047412\Desktop\proj.hex"