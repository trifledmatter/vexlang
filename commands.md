## vex <category> <command> [arguments...]

### Screen

---

vex screen clear
vex screen print <text> [x] [y]
vex screen setColor <c>

### Motor

---

vex motor <m> set <speed>
vex motor <m> stop
vex motor <m> setDirection <d>
vex motor <m> setPosition <p>
vex motor <m> setPower <p>
vex motor <m> setPID <p> <i> <d>
vex motor all stop

### Sensor

---

vex sensor <s> getReading
vex sensor <s> callibrate
vex sensor <s> reset
vex sensor <s> setRange
vex sensor all reset

### Motor Group Control

---

vex motors <gn> set <s>
vex motors <gn> stop
vex motors <gn> setDirection <d>

### Actions

---

vex robot move <dist> <s>
vex robot turn <angle> <s>
vex robot stop
vex robot reset

### Communication

---

vex comm send <msg>
vex comm receive
vex comm setChannel <cn>

### Debug

---

vex debug start
vex debug stop
vex diagnostics run
vex diagnostics getResults

### Power

---

vex battery getStatus
vex battery setPowerMode <mode>
vex battery saveEnergy
vex battery setThreshold <level>
