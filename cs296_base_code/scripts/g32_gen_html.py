f=open('./doc/g32_prof_report.tex','r')
out=open('final.html','w')
i=1
out.write("<html>")
for line in f:
	if line=="":
		continue	
	if line[0]=='\\' and line[1:5]=="date":
		date=line[6:]
		date=date[:-2]
		message="Date: "+date
		out.write(message)
	if line[0]=='\\' and line[1:7]=="author":
		temp=line[8:-2]
		temp=temp.replace("\\and","")
		temp=temp.replace("\\","")
		message="Authors are " + temp + "<br>"
		out.write(message)
	if line[0]=='\\' and line[1:6]=="title":
		heading1=line[15:]
		heading1=heading1[:-3]
		message="<h1 align='center' style='color:blue'><u>"+heading1+"</u></h1>"
		out.write(message)
	if line[0]=='\\' and line[1:8]=="section":
		heading2=line[9:-2]
		message="<h2 align='center' style='color:red'><u>"+heading2+"</u></h2>"
		out.write(message)
	if line[0]=='\\' and line[1:11]=="subsection":
		heading3=line[12:-2]
		message="<h3 style='color:green'><u>"+heading3+"</u></h3>"
		out.write(message)
	if line[0]=='\\' and line[1:16]=="includegraphics":
		ind1=line.index("{")
		ind2=line.index("}")
		image=line[ind1+1:ind2]
		message="<img style='width:500px' src=" + image + "></img><br>"
		out.write(message)
	if line[0]!='\\' and line[0]!="%" and len(line)>=3:
		message=line
		message=message.strip()
		if message[-2]=='\\' and message[-1]=='\\':
			message=message[:-2]
		message=message+"<br>"
		out.write(message)

out.write("</html>")	
		


out.close()
f.close()

f=open('final.html','r+')
out=open('./doc/g32_report.html','w')

for line in f:
	line=line.replace("\\times","*")
	line=line.replace("\\vec","")
	line=line.replace("{","")
	line=line.replace("}","")
	line=line.replace("\\cite","")
	if "\\frac" in line:
		g=line.index("\\frac")
		temp=line[g+6:]
		line=line[:g+6]+ "/" +temp
	line=line.replace("\\frac","")
	out.write(line)	
	

out.close()
f.close()
import os
os.remove("final.html")



	
