#!/usr/bin/python

# SUCCESS.PY
# When the transportation of a player from this room to another room is successful,
# this program edits the resources file of this room, namely,
# changes its OCCUPIED field from 1 to 0.

import csv, cgitb, cgi
cgitb.enable()

# Receive two parameters
form = cgi.FieldStorage()
# 1) Player's inventory
inventory = form.getvalue('inventory')	# NOT CHECKING IF THE TRANSPORTER PLAYER HAS 0 MANNA ATM, BUT MIGHT NEED TO
# 2) URL of the room the player came from (to the a.out/room.cgi file)
URL = form.getvalue('URL')

# URL = 'http://www.cs.mcgill.ca/~hgokse/cgi-bin/room.cgi' 	#??????

print "Content-type:text/html"
print ""

print "<html>"

r = csv.reader(open("../resources.csv"))
lines = [l for l in r]
lines[0][2] = '0'
writer = csv.writer(open("../resources.csv", 'w'))
writer.writerows(lines)

# Call other room's REFRESH
print('''
	Hit the 'Go!' button to go to the room!
	<form action="''' + URL + '''" method="post"> 
		<input type="hidden" name="inventory" value="'''+ inventory +'''">
   		<input type="text" name="command" value="refresh">
   		<input type="submit" value="Go!">
	</form>''')

print "</html>"

