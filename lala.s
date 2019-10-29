.name		"Lala!"
.comment	"Lala hop!"

	ld %0, r16
start:
	sti r1, %:live, %1
live:
	live %0
fork:
	fork %:start
	zjmp %:lala
lala:
	sti r1, %:alive, %1
alive:
	live %0
