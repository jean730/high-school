x=-70
y=35
z=150
speed = 10
while true do
ang=getAngX()
if key_shift() == 1 then
	if speed < 20 then
        speed = speed + 0.1
    end
else
	if speed > 1 then
        speed = speed - 0.1
    end
end
if key_up() == 1 then
	x=x+math.cos(math.rad(ang))*speed
	z=z+math.sin(math.rad(ang))*speed
end
if key_down() == 1 then
	x=x-math.cos(math.rad(ang))*speed
	z=z-math.sin(math.rad(ang))*speed
end
if key_left() == 1 then
	x=x-math.cos(math.rad(ang+90))*speed
	z=z-math.sin(math.rad(ang+90))*speed
end
if key_right() == 1 then
	x=x+math.cos(math.rad(ang+90))*speed
	z=z+math.sin(math.rad(ang+90))*speed
end
if key_space() == 1 then
	y=y+1*speed
end
if key_ctrl() == 1 then
	y=y-1*speed
end
setPos(x,y,z)
sleep(1000/60)
end
