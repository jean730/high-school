plane=createEntity("assets/models/x-35_obj.obj")
a=0
setLightPos(0,-210,110,210)
setLightPos(1,-190,110,190)
setLightColor(0,0,0,1)
setLightColor(1,1,0,0)
while true do
	a=a+0.2
	Dist=800
	setEntityAng(plane,0,a*0.2+math.pi/2,0)
	setEntityPos(plane,-200,90,200)
	setEntityScale(plane,0.5,0.5,0.5)
	sleep(1000/60)
end
