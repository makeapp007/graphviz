#parse.py
#parse sequence
#road,estate,sign

path="input.txt"
ff=open(path)
f=ff.readlines()
print len(f)
roadlen=int(f[1].replace("\n",""))
print roadlen
estatelen=int(f[1+roadlen+1])
print estatelen
signlen=int(f[1+roadlen+1+estatelen+1])
print signlen

# for f in ff.readlines():
# 	print f
# f=ff.read()
# print f

f2 = open('output.gv','w')
f2.write('graph G {\n') # python will convert \n to os.linesep
scale=30

#parse road
print f[roadlen+1]
for i in range(0,roadlen):	
	name="A"+"".join(f[2+i].split())
	nameend=name+"B"
	line=f[2+i].split()
	# print line
	# print name
	direction=int(line[0])
	pos=int(line[1])
	width=int(line[2])
	if width==0:
		widthstr="[penwidth=1]"
	elif width==1:
		widthstr="[penwidth=4]"
	else:
		widthstr="[penwidth=7]"
	func=int(line[3])
	if func==0:
		linestyle="[style=dashed]"
	else:
		linestyle=""
	if direction==0:
		x=pos*scale
		# print x 
		ystart=0
		yend=scale*scale
		print "north west"
		f2.write(name+" -- "+nameend+widthstr+linestyle+"\n")
		# f2.write(widthstr)

		f2.write( name+" [\n")
		f2.write( "pos =\""+str(x)+","+str(ystart)+"\"")
		# print "pos =\""+str(x)+","+str(yend)+"\""
		f2.write( '''
		\nwidth=0.05
		fixedsize=true\n style=filled\n
		color=black
		shape=circle\n
		label=""\n
		]\n
		''')
		f2.write( nameend+" [\n")
		f2.write( "\npos =\""+str(x)+","+str(yend)+"\" \n")
		# print "pos =\""+str(x)+","+str(yend)+"\""
		f2.write( '''
		\nwidth=0.05
		fixedsize=true\n style=filled\n
		color=black
		shape=circle\n
		label=""\n
		]\n
		''')
	if direction==1:
		y=pos*scale
		xstart=0
		xend=scale*scale
		print "north west"
		f2.write(name+" -- "+nameend+" "+widthstr+linestyle+"\n")
		f2.write( name+" [\n")
		f2.write( "pos =\""+str(xstart)+","+str(y)+"\"")
		f2.write( '''
		\nwidth=0.05
		fixedsize=true\n style=filled\n
		color=black
		shape=circle\n
		label=""\n
		]\n
		''')
		f2.write( nameend+" [\n")
		f2.write( "\npos =\""+str(xend)+","+str(y)+"\"")
		# print "pos =\""+str(x)+","+str(yend)+"\""
		f2.write( '''
		width=0.05
		fixedsize=true\n style=filled\n
		color=black
		shape=circle\n
		label=""\n
		]\n
		''')
print "----"
start=2+roadlen+1
end=2+roadlen+1+estatelen
# print f[start]
# print f[end-1]
for i in range(start,end):	
	name="A"+"".join(f[i].split())
	name=name.replace(".","C")
	# nameend=name+"B"
	print name
	# print nameend
	line=f[i].split()
	print line

	x=float(line[0])*scale
	y=float(line[1])*scale
	f2.write( name+" [\n")
	f2.write( "pos =\""+str(x)+","+str(y)+"\"")
	# print "pos =\""+str(x)+","+str(yend)+"\""
	f2.write( '''
	width=0.12
	fixedsize=true
	style=filled
	fillcolor="#9ACEEB"
	shape=doublecircle\n
	label=""
	]\n
	''')	
# print "------"
# print signlen
print "----"
start=2+roadlen+1+estatelen+1
end=2+roadlen+1+estatelen+signlen+1
# print start
# print end
# print f[start]
for i in range(start,end):	
	# print f[i]
	name="sign"+"".join(f[i].split())
	# print name
	line=f[i].split()
	# print line

	x=float(line[0])*scale
	y=float(line[1])*scale
	f2.write( name+" [\n")
	f2.write( "pos =\""+str(x)+","+str(y)+"\"")
	# print "pos =\""+str(x)+","+str(yend)+"\""
	f2.write( '''
	width=0.14
	fixedsize=true
	style=filled
	color=red
	shape=circle
	label=""
	]\n
	''')	
	# name="A"+"".join(f[i].split())

#end line
f2.write("}\n")

# A -- A1 [label="1"   ];
# A -- A2
# A-- A3
# A [
#     pos = "0,0!";
# 	width=0.2

# 	fixedsize=true
# 	style=filled
# 	color=black
# 	shape=circle;
# ]



f2.close()





